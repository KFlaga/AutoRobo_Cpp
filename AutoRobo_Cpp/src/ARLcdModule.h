#ifndef LCD_H_
#define LCD_H_

#include <vector>
#include "ARModule.h"
#include <stdint.h>

namespace AutoRobo
{
	/**
	 * Provides high-level control of lcd screen
	 */
	class LcdModule : public Module
	{
	private:
		enum class RequestType
		{
			Write4,
			SetWriteCommand,
			SetWriteData,
		};

		struct Request
		{
			RequestType type;
			uint8_t data;
		};

		std::vector<Request> _queue;
		uint8_t _text[16];
		bool _isBusy;

	public:
		LcdModule();

		// Initializes LCD pins and configures its working mode
		void start() override;
		void stop() override;

		// Process one next async request
		void update(TimeSpan timeSinceUpdate) override;

		// Indicates if lcd is currently waiting for
		// synchronous operation to be completed.
		bool isBusy() const
		{
			return _isBusy;
		}

		// Clears all text from lcd. Blocks for few ms.
		void clear();
		// Moves cursor to beginning of 1st line. Blocks for few ms.
		void home();

		// Writes an 8bit character on cursor position. Moves cursor. Blocks for few ms.
		void writeChar(uint8_t data);
		// Writes series of characters on 1st line from its beginning. Blocks for few ms.
		void writeUpperLine(uint8_t* data, uint8_t size);
		// Writes series of characters on 2nd line from its beginning. Blocks for few ms.
		void writeBottomLine(uint8_t* data, uint8_t size);

		// Clears all text from lcd. Moves cursor home.
		// Pushes request to asynchronous task queue.
		void clearAsync();
		// Moves cursor to beginning of 1st line.
		void homeAsync();
		// Writes an 8bit character.
		// Moves cursor to beginning of 1st line.
		void writeCharAsync(uint8_t data);
		// Writes series of characters on 1st line from its beginning. Blocks for few ms.
		void writeUpperLineAsync(uint8_t* data, uint8_t size);
		// Writes series of characters on 2nd line from its beginning. Blocks for few ms.
		void writeBottomLineAsync(uint8_t* data, uint8_t size);

		// Reads actual text from lcd
		void readContents();

		// Returns current contents of 1st line of lcd
		uint8_t* getUpperLineText();
		// Returns current contents of 2nd line of lcd
		uint8_t* getBottomLineText();

		// Cancels all waiting async requests.
		void clearRequests();

	private:
		void initPins();
		void setPinsToWrite();
		void setPinsToRead();

		void write4(uint8_t data);
		void write4Async(uint8_t data);
		void write4SetPins(uint8_t data);
		void writeLine(uint8_t* data, uint8_t size);
		void writeLineAsync(uint8_t* data, uint8_t size);

		void readLineContents(uint8_t lineAddress, uint8_t lineTextOffset);
	};
}

#endif
