/*
 * ARMainScreen.h
 *
 *  Created on: Apr 6, 2017
 *      Author: Kamil
 */

#ifndef MENU_ARMAINSTATE_H_
#define MENU_ARMAINSTATE_H_

#include "ARChooseOptionState.h"

namespace AutoRobo
{
	/**
	 * Initial state of programmer after reset.
	 * Inherits from ChooseOptionStateas - it allows to choose one of:
	 * - choose and execute single robot instruction
	 * - choose a stored program to execute or edit
	 * - create new program
	 * - reset system
	 */
	class MainState : public ChooseOptionState
	{
	public:
		MainState(ProgrammerModule* module);

		void start() override;
		void stop() override;
	};
}

#endif /* MENU_ARMAINSTATE_H_ */
