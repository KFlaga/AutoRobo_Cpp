#include "ARChooseInstructionState.h"
#include "../movement/ARRoboProgram.h"

using namespace AutoRobo;

ChooseInstructionState::ChooseInstructionState(
	std::function<void(RoboInstruction*)> instrCallback,
	ProgrammerModule* module,
	ProgrammerState* parent) :
		ProgrammerState(module, parent),
				_fwdCallback(instrCallback)
{

}

void ChooseInstructionState::start()
{
	_curInstr = 0;
	if(_instrCount > 0)
	{
		memcpy(_bottomLine, _instructions[_curInstr].definition->name, 8);
	}
}

void ChooseInstructionState::onButtonUp()
{
	if(_curInstr > 0)
	{
		_curInstr -= 1;
		memcpy(_bottomLine, _instructions[_curInstr].definition->name, 8);

		refreshBottomText();
	}
}

void ChooseInstructionState::onButtonDown()
{
	if(_curInstr < _instrCount - 1)
	{
		_curInstr += 1;
		memcpy(_bottomLine, _instructions[_curInstr].definition->name, 8);

		refreshBottomText();
	}
}

void ChooseInstructionState::onButtonFwd()
{
	if(_instrCount > 0)
	{
		_fwdCallback(_instructions[_curInstr]);
	}
}

void ChooseInstructionState::onButtonBwd()
{
	returnToParent();
}

