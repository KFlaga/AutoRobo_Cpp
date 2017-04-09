#ifndef MENU_ARPROGRAMMERSTATE_H_
#define MENU_ARPROGRAMMERSTATE_H_

#include "../ARUtils.h"
#include "../ARTimeSpan.h"

namespace AutoRobo
{
	class ProgrammerModule;

	/**
	 * Base class for programmer states.
	 * Programmer is in one of states every time and depending
	 * on its current state it changes a way to handle keyboard input
	 * and text to show on LCD screen.
	 */
	class ProgrammerState
	{
	protected:
		ProgrammerModule* _module;
		ProgrammerState* _parent;
		unsigned char _upperLine[17];
		unsigned char _bottomLine[17];

	public:
		ProgrammerState(ProgrammerModule* module, ProgrammerState* parent = 0) :
				_module(module), _parent(parent)
		{

		}

		virtual void start() { }
		virtual void stop() { }

		virtual void update(TimeSpan timeSinceLastUpdate)
		{
		}

		virtual void onButtonLeft()
		{
		}
		virtual void onButtonRight()
		{
		}
		virtual void onButtonUp()
		{
		}
		virtual void onButtonDown()
		{
		}
		virtual void onButtonFwd()
		{
		}
		virtual void onButtonBwd()
		{
		}

		void returnToParent();
		void refreshBottomText();
		void refreshUpperText();
	};

}

#endif /* MENU_ARPROGRAMMERSTATE_H_ */
