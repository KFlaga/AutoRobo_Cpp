//#include "ButtonModule.h"
//#include "LcdModule.h"
//

#include "ARButtonsModule.h"
#include "ARPins.h"

namespace AutoRobo
{

	/*
	 * Buttons codes:
	 * eh a0 a1 : 0bxxx
	 */
	static constexpr uint8_t buttonCode_Up = 0b100;
	static constexpr uint8_t buttonCode_Down = 0b001;
	static constexpr uint8_t buttonCode_Left = 0b101;
	static constexpr uint8_t buttonCode_Right = 0b000;
	static constexpr uint8_t buttonCode_Fwd = 0b011;
	static constexpr uint8_t buttonCode_Bwd = 0b010;
	static constexpr uint8_t buttonCode_Switch1 = 0b110;
	static constexpr uint8_t buttonCode_Switch2 = 0b110;

	static inline bool getMuxA0(const uint8_t buttonCode)
	{
		return (buttonCode & 1) > 0;
	}

	static inline bool getMuxA1(const uint8_t buttonCode)
	{
		return (buttonCode & 2) > 0;
	}

	static inline bool getMuxE(const uint8_t buttonCode)
	{
		return (buttonCode & 4) > 0;
	}

	ButtonsModule::ButtonsModule() :
			Module(getTypeId<ButtonsModule>())
	{

		ButtonPins::muxA0.setAsOutput();
		ButtonPins::muxA0.setHighSpeed();
		ButtonPins::muxA0.setPushPullEnabled();
		ButtonPins::muxA0.setPushUp();

		ButtonPins::muxA1.setAsOutput();
		ButtonPins::muxA1.setHighSpeed();
		ButtonPins::muxA1.setPushPullEnabled();
		ButtonPins::muxA1.setPushUp();

		ButtonPins::muxEN.setAsOutput();
		ButtonPins::muxEN.setHighSpeed();
		ButtonPins::muxEN.setPushPullEnabled();
		ButtonPins::muxEN.setPullDown();

		ButtonPins::muxRead.setAsInput();
		ButtonPins::muxRead.setHighSpeed();
		ButtonPins::muxRead.setPushPullEnabled();
		ButtonPins::muxRead.setPushUp();

		_buttonUpdateInterval = Milisecond(30);
	}

	ButtonsModule::~ButtonsModule()
	{

	}

	void ButtonsModule::update(TimeSpan timeSinceUpdate)
	{
		_buttonUpdateRemainingTime = _buttonUpdateRemainingTime
				- timeSinceUpdate;
		if(_buttonUpdateRemainingTime == TimeSpan())
		{
			// Set successive buttons pins combinations
			// For each button save its old state
			// Read and update the current state
			_oldOldState = _oldState;
			_oldState = _currentState;
			_currentState = 0;
			for(uint8_t but = 0; but < 8; but++)
			{
				// Checking buttons:
				// Set: [e1,a0,a1] = [0,0,0] -> 1st button
				// Check: high = not pressed, low = pressed

				uint16_t butFlag = 1 << but;
				setMuxPins(but);
				uint8_t newState =
						ButtonPins::muxRead.isLow() ?
								ButtonState::Pressed : ButtonState::Released;
				_currentState |= (newState << but);

				// if up and left is down - only up is down ( more specific buts 5 and 4 )
				if(but == 5 && isButtonPressed((Buttons)4))
				{
					_currentState &= ~((uint16_t)butFlag); // reset 5th button state
				}
			}
			_buttonUpdateRemainingTime = _buttonUpdateInterval;
		}
	}

	void ButtonsModule::start()
	{
		_currentState = 0;
		_oldState = 0;
		_oldOldState = 0;
		_buttonUpdateRemainingTime = _buttonUpdateInterval;
	}

	void ButtonsModule::stop()
	{
		_currentState = 0;
		_oldState = 0;
		_oldOldState = 0;
	}

	void ButtonsModule::setMuxPins(uint8_t code)
	{
		if(getMuxA0(code))
			ButtonPins::muxA0.setHigh();
		else
			ButtonPins::muxA0.setLow();

		if(getMuxA1(code))
			ButtonPins::muxA1.setHigh();
		else
			ButtonPins::muxA1.setLow();

		if(getMuxE(code))
			ButtonPins::muxEN.setHigh();
		else
			ButtonPins::muxEN.setLow();

		// Some little delay for GPIO and MUX/Gates to stabilize
		// ( ~= 200ns should do ~= 20 cycles )
		for(code = 0; code < 4; code++)
			asm("nop");
	}
}
