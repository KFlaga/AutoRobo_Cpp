/*
 * ARLcdHandler.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: Kamil
 */

#include "ARLcdModule.h"

#include "ARPins.h"
#include "ARSystemTimer.h"

namespace AutoRobo
{
	namespace LcdCodes
	{
		constexpr uint8_t Reset_4bit = 0x3;
		constexpr uint8_t Interface4Bit_4bit = 0x2;
		constexpr uint8_t Interface4Bit2Lines = 0x28;
		constexpr uint8_t DisplayOff = 0x08;
		constexpr uint8_t ClearScreen = 0x01;
		constexpr uint8_t DisplayOnCursorOn = 0x0F;
		constexpr uint8_t DisplayOnCursorOff = 0x0D;
		constexpr uint8_t EntryIncrementCursor = 0x06;
		constexpr uint8_t Home = 0x02;

		// Move cursor to line :
		// [D7-D1] = [1aaaaaaa], where a is address
		// for first line its 0 : 0x80 + 0x00
		// for second line its 40 : 0x80 + 0x40 = 0xC0
		constexpr uint8_t MoveCursotToUpperLine = 0x80;
		constexpr uint8_t MoveCursotToBottomLine = 0xC0;
	}

	static inline void setRsCommand()
	{
		LcdPins::RS.setLow();
	}

	static inline void setRsData()
	{
		LcdPins::RS.setHigh();
	}

	static inline void setRwWrite()
	{
		LcdPins::RW.setLow();
	}

	static inline void setRwRead()
	{
		LcdPins::RW.setHigh();
	}

	static inline void setEnabled()
	{
		LcdPins::E.setHigh();
	}

	static inline void setDisabled()
	{
		LcdPins::E.setLow();
	}

	LcdModule::LcdModule() :
			Module(getTypeId<LcdModule>())
	{

	}

	void LcdModule::update(TimeSpan )
	{
		if(_isBusy)
			return;

		while(_queue.size() > 0)
		{
			Request req = *_queue.begin();
			_queue.erase(_queue.begin());
			switch(req.type)
			{
				case RequestType::Write4 :
					write4Async(req.data);
					return;
				case RequestType::SetWriteCommand :
					setRsCommand();
					break;
				case RequestType::SetWriteData :
					setRsData();
					break;
			}
		}
	}

	void LcdModule::start()
	{
		initPins();
		setPinsToWrite();

		wait(Milisecond(100));

		setRsCommand();

		// Reset lcd and set 4bit interface
		write4(LcdCodes::Reset_4bit);
		wait(Milisecond(25));
		write4(LcdCodes::Reset_4bit);
		wait(Milisecond(25));
		write4(LcdCodes::Reset_4bit);
		wait(Milisecond(5));

		// Enable 4 bit mode
		write4(LcdCodes::Interface4Bit_4bit);
		wait(Milisecond(5));

		// Set default operating options
		writeChar(LcdCodes::Interface4Bit2Lines);
		writeChar(LcdCodes::DisplayOff);
		writeChar(LcdCodes::ClearScreen);
		writeChar(LcdCodes::EntryIncrementCursor); // Set increment cursor
		writeChar(LcdCodes::DisplayOnCursorOn);

		setRsData();
	}

	void LcdModule::initPins()
	{
		LcdPins::D4.setAsOutput();
		LcdPins::D5.setAsOutput();
		LcdPins::D6.setAsOutput();
		LcdPins::D7.setAsOutput();
		LcdPins::E.setAsOutput();
		LcdPins::RS.setAsOutput();
		LcdPins::RW.setAsOutput();

		LcdPins::D4.setMedSpeed();
		LcdPins::D5.setMedSpeed();
		LcdPins::D6.setMedSpeed();
		LcdPins::D7.setMedSpeed();
		LcdPins::E.setMedSpeed();
		LcdPins::RS.setMedSpeed();
		LcdPins::RW.setMedSpeed();

		LcdPins::D4.setPushPullEnabled();
		LcdPins::D5.setPushPullEnabled();
		LcdPins::D6.setPushPullEnabled();
		LcdPins::D7.setPushPullEnabled();
		LcdPins::E.setPushPullEnabled();
		LcdPins::RS.setPushPullEnabled();
		LcdPins::RW.setPushPullEnabled();

		LcdPins::D4.setPushUp();
		LcdPins::D5.setPushUp();
		LcdPins::D6.setPushUp();
		LcdPins::D7.setPushUp();
		LcdPins::E.setPushUp();
		LcdPins::RS.setPushUp();
		LcdPins::RW.setPushUp();

		LcdPins::E.setLow();
		LcdPins::RW.setLow();
	}

	void LcdModule::setPinsToWrite()
	{
		LcdPins::D4.setAsOutput();
		LcdPins::D5.setAsOutput();
		LcdPins::D6.setAsOutput();
		LcdPins::D7.setAsOutput();
	}

	void LcdModule::setPinsToRead()
	{
		LcdPins::D4.setAsInput();
		LcdPins::D5.setAsInput();
		LcdPins::D6.setAsInput();
		LcdPins::D7.setAsInput();
	}

	void LcdModule::write4(uint8_t data)
	{
		write4SetPins(data);
		setEnabled();
		wait(Milisecond(1));
		setDisabled();
	}

	void LcdModule::write4Async(uint8_t data)
	{
		write4SetPins(data);
		setEnabled();
		SystemTimer::getSystemTimer().registerOneShotCallback([]()
		{
			setDisabled();
		}, Milisecond(1));
	}

	void LcdModule::write4SetPins(uint8_t data)
	{
		if(data & 1)
			LcdPins::D4.setHigh();
		else
			LcdPins::D4.setLow();
		if(data & 2)
			LcdPins::D5.setHigh();
		else
			LcdPins::D5.setLow();
		if(data & 4)
			LcdPins::D6.setHigh();
		else
			LcdPins::D6.setLow();
		if(data & 8)
			LcdPins::D7.setHigh();
		else
			LcdPins::D7.setLow();
	}

	void LcdModule::clear()
	{
		setRsCommand();
		writeChar(LcdCodes::ClearScreen);
		setRsData();
	}

	void LcdModule::home()
	{
		setRsCommand();
		writeChar(LcdCodes::Home);
		setRsData();
	}

	void LcdModule::writeChar(uint8_t data)
	{
		_isBusy = true;
		write4(data >> 4);
		wait(Milisecond(2));
		write4(data);
		wait(Milisecond(5));
		_isBusy = false;
	}

	void LcdModule::writeLine(uint8_t* data, uint8_t size)
	{
		_isBusy = true;
		for(uint8_t i = 0; i < size; ++i)
		{
			writeChar(data[i]);
			_isBusy = true;
		}
		_isBusy = false;
	}

	void LcdModule::writeUpperLine(uint8_t* data, uint8_t size)
	{
		setRsCommand();
		writeChar(LcdCodes::MoveCursotToUpperLine);
		setRsData();
		writeLine(data, size);
	}

	void LcdModule::writeBottomLine(uint8_t* data, uint8_t size)
	{
		setRsCommand();
		writeChar(LcdCodes::MoveCursotToBottomLine);
		setRsData();
		writeLine(data, size);
	}

	void LcdModule::clearAsync()
	{
		_queue.push_back(Request { RequestType::SetWriteCommand, 0 });
		writeCharAsync(LcdCodes::ClearScreen);
		_queue.push_back(Request { RequestType::SetWriteData, 0 });
	}

	void LcdModule::homeAsync()
	{
		_queue.push_back(Request { RequestType::SetWriteCommand, 0 });
		writeCharAsync(LcdCodes::Home);
		_queue.push_back(Request { RequestType::SetWriteData, 0 });
	}

	void LcdModule::writeCharAsync(uint8_t data)
	{
		_queue.push_back(Request { RequestType::Write4, (uint8_t)(data >> 4) });
		_queue.push_back(Request { RequestType::Write4, data });
	}

	void LcdModule::writeLineAsync(uint8_t* data, uint8_t size)
	{
		for(uint8_t i = 0; i < size; ++i)
		{
			writeCharAsync(data[i]);
		}
	}

	void LcdModule::writeUpperLineAsync(uint8_t* data, uint8_t size)
	{
		_queue.push_back(Request { RequestType::SetWriteCommand, 0 });
		writeCharAsync(LcdCodes::MoveCursotToUpperLine);
		_queue.push_back(Request { RequestType::SetWriteData, 0 });
		writeLineAsync(data, size);
	}

	void LcdModule::writeBottomLineAsync(uint8_t* data, uint8_t size)
	{
		_queue.push_back(Request { RequestType::SetWriteCommand, 0 });
		writeCharAsync(LcdCodes::MoveCursotToBottomLine);
		_queue.push_back(Request { RequestType::SetWriteData, 0 });
		writeLineAsync(data, size);
	}

	static uint8_t readLcd()
	{
		uint8_t data = 0;
		data |= LcdPins::D4.isHigh() ? 1 : 0;
		data |= LcdPins::D5.isHigh() ? 2 : 0;
		data |= LcdPins::D6.isHigh() ? 4 : 0;
		data |= LcdPins::D7.isHigh() ? 8 : 0;

		return data;
	}

	void LcdModule::readContents()
	{
		home();
		readLineContents(0x00, 0);
		readLineContents(0x40, 8);
	}

	void LcdModule::readLineContents(uint8_t lineAddress,
		uint8_t lineTextOffset)
	{
		for(int i = 0; i < 8; ++i)
		{
			setPinsToWrite();
			setRsCommand();
			setRwWrite();
			// Set address : 0b[1aaa][aaaa]
			writeChar(0x80 | lineAddress | i);

			setPinsToRead();
			setRsData();
			setRwRead();

			// Read : Rw = 1 Rs = 1 0b[dddd][dddd]
			setEnabled();
			wait(Milisecond(1));
			setDisabled();
			_text[i + lineTextOffset] = readLcd() << 4;
			_text[i + lineTextOffset] |= readLcd();
		}
	}

	uint8_t* LcdModule::getUpperLineText()
	{
		return &_text[0];
	}

	uint8_t* LcdModule::getBottomLineText()
	{
		return &_text[8];
	}

	void LcdModule::clearRequests()
	{
		_queue.clear();
	}
}

