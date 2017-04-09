#ifndef MENU_ARCHOOSEOPTIONSTATE_H_
#define MENU_ARCHOOSEOPTIONSTATE_H_

#include "ARProgrammerState.h"

namespace AutoRobo
{
	/**
	 * Option to choose for 'ChooseOptionState'
	 */
	class ProgrammerOption
	{
		unsigned char* _name;
		ProgrammerState* _state;
	public:
		ProgrammerOption(ProgrammerState* state, unsigned char* name) :
				_name(name), _state(state)
		{
		}

		ProgrammerState* getState() const
		{
			return _state;
		}

		unsigned char* getName() const
		{
			return _name;
		}
	};

	/**
	 * Base state for menus which only allow user to choose
	 * one of options and move to corresponding state.
	 * Array of options must be set by 'setOptions()' before state starts and
	 *
	 * Text for this state is:
	 * - state name on upper line
	 * - chosen option name on bottom line
	 */
	class ChooseOptionState : public ProgrammerState
	{
		ProgrammerOption* _options;
		int _optionsCount;
		int _currentOption;

	protected:
		void setOptions(ProgrammerOption* options, int optionsCount)
		{
			_options = options;
			_optionsCount = optionsCount;
		}

	public:
		ChooseOptionState(ProgrammerModule* module, ProgrammerState* parent) :
				ProgrammerState(module, parent)
		{
		}

		// Chooses first option (assumes there's at least one)
		void start() override;

		// Chooses previous option
		void onButtonUp() override;
		// Chooses next option
		void onButtonDown() override;
		// Selects current option
		void onButtonFwd() override;
		// Returns to parent
		void onButtonBwd() override;
	};
}

#endif /* MENU_ARCHOOSEOPTIONSTATE_H_ */
