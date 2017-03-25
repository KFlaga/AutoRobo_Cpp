/*
 * ARModule.h
 *
 *  Created on: Mar 23, 2017
 *      Author: Kamil
 */

#ifndef ARMODULE_H_
#define ARMODULE_H_

#include "ARTimeSpan.h"

namespace AutoRobo
{
	static const TimeSpan moduleTick = Milisecond(5);

	// Interface for generic program module, which needs regular updates.
	// Each module should be responsible for one task, like
	// handling peripherals (i.e. buttons, motors), handling programmer menu or updating movement
	// Modules are added and updated by ModuleManager, which allows for easy extensions
	class Module
	{
	protected:
		TypeId _typeId;

	public:
		Module(TypeId type) :
			_typeId(type)
		{
		}

		// Updates module
		// Passed TimeSpan is time since last update of this module
		virtual void update(TimeSpan timeSinceUpdate) = 0;

		virtual void start() = 0;
		virtual void stop() = 0;

		TypeId getType() const
		{
			return _typeId;
		}
	};

}

#endif /* ARMODULE_H_ */
