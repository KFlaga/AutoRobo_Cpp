#include "ARMainState.h"

#include "ARExecuteSingleInstructionState.h"
#include "ARResetState.h"

using namespace AutoRobo;

static unsigned char _optNameSingleInstruction[16] __attribute__ ((section(".rodata")))
= { 'P', 'o', 'j', 'e', 'd', '.', ' ', 'I',
		'n', 's', 't', 'r', '.', ' ', ' ', ' ' };

static unsigned char _optNameReset[16] __attribute__ ((section(".rodata")))
= { 'R', 'e', 's', 'e', 't', ' ', 'S', 'y',
		's', 't', 'e', 'm', 'u', ' ', ' ', ' ' };

MainState::MainState(ProgrammerModule* module) :
		ChooseOptionState(module, 0)
{
	static ProgrammerState states[] = {
			ChooseSingleInstructionState(module, this),
			ResetState(module, this)
	};

	static ProgrammerOption options[] = {
			ProgrammerOption(&states[0], &_optNameSingleInstruction[0]),
			ProgrammerOption(&states[1], &_optNameReset[0])
	};

	setOptions(&options[0], 2);
}

void MainState::start()
{
	ChooseOptionState::start();
}

void MainState::stop()
{
	ChooseOptionState::stop();
}

