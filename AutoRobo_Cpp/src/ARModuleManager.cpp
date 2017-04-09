/*
 * ARModuleManager.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: Kamil
 */

#include "ARModuleManager.h"
#include "ARTimer.h"
#include <vector>
#include <algorithm>

namespace AutoRobo
{
	static std::vector<Module*> _modules;

	ModuleManager::ModuleManager()
	{

	}

	ModuleManager::~ModuleManager()
	{
		unregisterAll();
	}

	void ModuleManager::start(not_null<Timer*> timer, TimeSpan updateInterval)
	{
		if(!_isRunning)
		{
			_timer = timer;
			if(updateInterval > Microsecond(1))
			{
				for(auto module : _modules)
				{
					module->start();
				}

				timer->start([this](TimeSpan)
				{
					this->update();
				}, updateInterval);
				_isRunning = true;
			}
		}
	}

	void ModuleManager::stop()
	{
		if(_isRunning)
		{
			_timer->stop();
			for(auto module : _modules)
			{
				module->stop();
			}
			_isRunning = false;
		}
	}

	void ModuleManager::registerModule(not_null<Module*> module)
	{
		_modules.push_back(module);
		if(_isRunning)
		{
			module->start();
		}
	}

	void ModuleManager::unregisterModule(Module* module)
	{
		auto moduleIt = std::find(_modules.begin(), _modules.end(), module);
		if(_modules.end() != moduleIt)
		{
			if(_isRunning)
			{
				module->stop();
			}
			_modules.erase(moduleIt);
		}

	}

	void ModuleManager::update()
	{
		if(_isRunning)
		{
			for(auto module : _modules)
			{
				module->update(_timer->getCurrentTime());
			}
		}
	}

	void ModuleManager::unregisterAll()
	{
		stop();
		_modules.clear();
	}

	Module* ModuleManager::findModule(TypeId typeId)
	{
		auto moduleIt = std::find_if(_modules.begin(), _modules.end(),
				[typeId](Module* modulePtr) -> bool
				{
					return (modulePtr->getType() == typeId);
				});
		if(_modules.end() != moduleIt)
		{
			return *moduleIt;
		}
		return nullptr;
	}
}

