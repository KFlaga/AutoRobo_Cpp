/*
 * ARButtonsModule.h
 *
 *  Created on: Mar 25, 2017
 *      Author: Kamil
 */

#ifndef ARBUTTONSMODULE_H_
#define ARBUTTONSMODULE_H_

#include "ARPins.h"
#include "ARModule.h"

namespace AutoRobo
{
	class ButtonsModule : public Module
	{
	public:
		enum ButtonState
			: uint8_t
			{
				Pressed = 1, Released = 0
		};

		enum Buttons
			: uint16_t
			{
				ButtonUp = 1 << 0,
			ButtonDown = 1 << 1,
			ButtonLeft = 1 << 2,
			ButtonRight = 1 << 3,
			ButtonForward = 1 << 4,
			ButtonBackward = 1 << 5,
			ButtonSwitch1 = 1 << 6,
			ButtonSwitch2 = 1 << 7,
		};
	protected:
		TimeSpan _buttonUpdateInterval;
		TimeSpan _buttonUpdateRemainingTime;
		uint16_t _oldState;
		uint16_t _oldOldState;
		uint16_t _currentState;

	public:
		ButtonsModule();
		~ButtonsModule();

		void update(TimeSpan timeSinceUpdate);
		void start();
		void stop();

		uint16_t getButtonStates() const
		{
			return _currentState;
		}

		bool isButtonPressed(Buttons but) const
		{
			return (getButtonStates() & but) == ButtonState::Pressed;
		}

		bool isButtonReleased(Buttons but) const
		{
			return (getButtonStates() & but) == ButtonState::Released;
		}

		bool wasButtonPressedLastUpdate(Buttons but) const
		{
			// Now pressed, last time and 2 updates ago released
			return (_currentState & but) > 0 && (_oldState & but) > 0
					&& (_oldOldState & but) == 0;
		}

		bool wasButtonReleasedLastUpdate(Buttons but) const
		{
			// Now released, last time and 2 updates ago pressed
			return (_currentState & but) == 0 && (_oldState & but) == 0
					&& (_oldOldState & but) > 0;
		}

		TimeSpan getButtonUpdateInterval() const
		{
			return _buttonUpdateInterval;
		}

		void setButtonUpdateInterval(TimeSpan interval)
		{
			_buttonUpdateInterval = interval;
		}

	protected:
		void setMuxPins(uint8_t code);
	};
}

#endif /* ARBUTTONSMODULE_H_ */
