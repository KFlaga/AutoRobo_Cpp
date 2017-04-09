/*
 * ARModuleManager.h
 *
 *  Created on: Mar 23, 2017
 *      Author: Kamil
 */

#ifndef ARMODULEMANAGER_H_
#define ARMODULEMANAGER_H_

#include "ARModule.h"

namespace AutoRobo
{
	class Timer;

	// Stores and updates modules
	class ModuleManager
	{
	public:
		static ModuleManager& getModuleManager()
		{
			static ModuleManager instance;
			return instance;
		}

	private:
		Timer* _timer;
		bool _isRunning;

	private:
		ModuleManager();

	public:
		~ModuleManager();

		// Starts updating registered modules
		// Uses supplied timer and interval for this task
		// Calls 'start' on each module
		// If manager is already running, does nothing
		void start(not_null<Timer*> timer, TimeSpan updateInterval);

		// Stops updating modules
		// Calls 'stop' on each module
		// If manager is not running, does nothing
		void stop();

		// Registers module for updates
		// If Manager is started, then it calls 'start' on this module and updates with others
		// Must not be called from within 'update' of any module
		void registerModule(not_null<Module*> module);

		// Unregisters module from updates
		// If Manager is started, then it calls 'stop' on this module
		// Must not be called from within 'update' of any module
		// If no such module is registered does nothing
		void unregisterModule(Module* module);

		// Unregisters module from updates
		// If Manager is started, then it calls 'stop' on this module
		// Must not be called from within 'update' of any module
		// If no such module is registered does nothing
		void unregisterModule(TypeId typeId)
		{
			unregisterModule(findModule(typeId));
		}

		// Removes all modules
		// If manager is running, stops first
		void unregisterAll();

		// Returns module with given TypeId if such is registered or nullptr
		Module* findModule(TypeId typeId);
	private:
		void update();
	};

}

#endif /* ARMODULEMANAGER_H_ */
