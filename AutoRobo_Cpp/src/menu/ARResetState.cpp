#include "ARResetState.h"
#include "stm32f4xx.h"

namespace AutoRobo
{
	ResetState::ResetState(ProgrammerModule* module, ProgrammerState* parent) :
			ProgrammerState(module, parent)
	{

	}

	void ResetState::start()
	{
		NVIC_SystemReset();
	}
}

