#ifndef MENU_ARRESETSTATE_H_
#define MENU_ARRESETSTATE_H_

#include "ARProgrammerState.h"

namespace AutoRobo
{
	/**
	 * Resets system on start
	 */
	class ResetState : public ProgrammerState
	{
	public:
		ResetState(ProgrammerModule* module, ProgrammerState* parent = 0);

		// Performs software reset
		void start() override;
	};
}


#endif /* MENU_ARRESETSTATE_H_ */
