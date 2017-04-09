#ifndef MENU_ARPROGRAMMERMODULE_H_
#define MENU_ARPROGRAMMERMODULE_H_

#include "../ARModule.h"

namespace AutoRobo
{
	class ProgrammerModule : public Module
	{
	public:
		ProgrammerModule();

		void update(TimeSpan timeSinceUpdate);
		void start();
		void stop();

		void setCurrentState(ProgrammerState* screen);
		ProgrammerState* getCurrentState() const;

		void updateUpperLineText();
		void updateBottomLineText();
	};
}

#endif /* MENU_ARPROGRAMMERMODULE_H_ */
