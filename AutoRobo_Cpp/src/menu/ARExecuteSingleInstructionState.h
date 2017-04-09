#ifndef MENU_AREXECUTESINGLEINSTRUCTIONSTATE_H_
#define MENU_AREXECUTESINGLEINSTRUCTIONSTATE_H_

#include "ARProgrammerState.h"

namespace AutoRobo
{
	/**
	 * Allows to execute single robo instruction.
	 * First switches to ChooseFunctionState.
	 * After function is chosen switches to create instruction state.
	 * After instruction is created switches to ExecuteInstruction state.
	 * After instruction is finished returns to parent.
	 */
	class ExecuteSingleInstructionState : public ProgrammerState
	{
	public:
		ExecuteSingleInstructionState(ProgrammerModule* module,
			ProgrammerState* parent = 0);

		// Chooses first instruction
		void start() override;

		// Chooses previous instruction
		void onButtonUp() override;
		// Chooses next option
		void onButtonDown() override;
		// Selects current option
		void onButtonFwd() override;
		// Returns to parent
		void onButtonBwd() override;
	};
}

#endif /* MENU_AREXECUTESINGLEINSTRUCTIONSTATE_H_ */
