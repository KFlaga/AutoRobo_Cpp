#include "ARChooseOptionState.h"
#include <string.h>
#include "ARProgrammerModule.h"

using namespace std;
using namespace AutoRobo;

void ChooseOptionState::start()
{
	_currentOption = 0;
	memcpy(_bottomLine, _options[0].getName(), 16);
}

void ChooseOptionState::onButtonUp()
{
	if(_currentOption > 0)
	{
		_currentOption -= 1;
		memcpy(_bottomLine, _options[_currentOption].getName(), 16);

		refreshBottomText();
	}
}

void ChooseOptionState::onButtonDown()
{
	if(_currentOption < _optionsCount - 1)
	{
		_currentOption += 1;
		memcpy(_bottomLine, _options[_currentOption].getName(), 16);

		refreshBottomText();
	}
}

void ChooseOptionState::onButtonFwd()
{
	_module->setCurrentState(_options[_currentOption].getState());
}

void ChooseOptionState::onButtonBwd()
{
	if(_parent != 0)
	{
		returnToParent();
	}
}

