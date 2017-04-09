/*
 * ARChooseInstructionState.h
 *
 *  Created on: Apr 8, 2017
 *      Author: Kamil
 */

#ifndef MENU_ARCHOOSEINSTRUCTIONSTATE_H_
#define MENU_ARCHOOSEINSTRUCTIONSTATE_H_

#include "ARProgrammerState.h"
#include <functional>

namespace AutoRobo
{
	class RoboFunctionDefinition;

	/**
	 * State that allows to choose a robo instruction from list.
	 * Array of options must be set by 'setOptions()' before state starts and
	 *
	 * Text for this state is:
	 * - state name on upper line
	 * - chosen instruction name on bottom line with position number
	 *
	 * Buttons Up and Down serves to choose an instruction.
	 * On Fwd it calls callback supplied in constructor with chosen instruction
	 * On Bwd it cancels and returns to parent.
	 */
	class ChooseInstructionState : public ProgrammerState
	{
		RoboInstruction* _instructions;
		int _instrCount;
		int _curInstr;
		std::function<void(RoboInstruction*)> _fwdCallback;

	public:
		ChooseInstructionState(
			std::function<void(RoboInstruction*)> instrCallback,
			ProgrammerModule* module,
			ProgrammerState* parent = 0);

		void setInstructions(RoboInstruction* instructions, int count)
		{
			_instructions = instructions;
			_instrCount = count;
		}

		// Chooses first instruction
		void start() override;

		// Chooses previous instruction
		void onButtonUp() override;
		// Chooses next instruction
		void onButtonDown() override;
		// Calls '_fwdCallback' with chosen instruction
		void onButtonFwd() override;
		// Returns to parent
		void onButtonBwd() override;
	};
}
#endif /* MENU_ARCHOOSEINSTRUCTIONSTATE_H_ */
