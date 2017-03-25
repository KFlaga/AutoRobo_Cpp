/*
 * ModuleTests.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: Kamil
 */

#include "TestsPreReqs.h"
#include "TestGroups.h"
#include "ARMath.h"
#include "ARModuleManager.h"
#include "ARTimer.h"
#include "ARSystemTimer.h"

using namespace AutoRobo;

class DummyModule : public Module
{
public:
	int counter;
	bool isRunning;

	DummyModule() :
			Module(getTypeId<DummyModule>()), counter(0), isRunning(false)
	{
	}

	void update(TimeSpan)
	{

	}

	void start()
	{
		counter = 0;
		isRunning = true;
	}

	void stop()
	{
		isRunning = false;
	}
};

class StartStopDummyModuleTest : public UTest::TestBase
{
public:
	StartStopDummyModuleTest() :
			TestBase("StartStopDummyModuleTest")
	{
	}

	void test() override
	{
		ModuleManager& mgr = ModuleManager::getModuleManager();
		DummyModule module;
		mgr.registerModule(&module);

		mgr.start(Timer::getTimer(moduleManagerTimerId), Milisecond(10));
		assertTrue(true == module.isRunning);

		mgr.stop();
		assertTrue(false == module.isRunning);

		mgr.unregisterModule(&module);

	}
};

class UpdateDummyModuleTest : public UTest::TestBase
{
public:
	UpdateDummyModuleTest() :
			TestBase("UpdateDummyModuleTest")
	{
	}

	void test() override
	{
		ModuleManager& mgr = ModuleManager::getModuleManager();
		DummyModule module;
		mgr.registerModule(&module);

		mgr.start(Timer::getTimer(moduleManagerTimerId), Milisecond(10));

		wait(Milisecond(22));

		assertTrue(2 == module.counter);

		mgr.stop();
		mgr.unregisterModule(&module);
	}
};

class FindDummyModuleTest : public UTest::TestBase
{
public:
	FindDummyModuleTest() :
			TestBase("FindDummyModuleTest")
	{
	}

	void test() override
	{
		ModuleManager& mgr = ModuleManager::getModuleManager();
		DummyModule module;
		mgr.registerModule(&module);

		Module* foundModule = mgr.findModule(getTypeId<DummyModule>());
		assertTrue(&module == foundModule);

		mgr.unregisterModule(&module);
	}
};

ModuleTestGroup::ModuleTestGroup() :
		TestGroup("ModuleTestGroup")
{
	ADD_TEST(StartStopDummyModuleTest);
	ADD_TEST(UpdateDummyModuleTest);
	ADD_TEST(FindDummyModuleTest);

	setIsEndOnFail(false);
}

void ModuleTestGroup::init()
{

}

void ModuleTestGroup::deinit()
{

}
