/*
 * ButtonsModuleTests.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: Kamil
 */

#include "TestsPreReqs.h"
#include "TestGroups.h"
#include "ARPins.h"
#include "ARButtonsModule.h"
#include "ARModuleManager.h"
#include "ARSystemTimer.h"

using namespace AutoRobo;

static ButtonsModule* getButtonsModule()
{
	return (ButtonsModule*)ModuleManager::getModuleManager().findModule(
			getTypeId<ButtonsModule>());
}

class ButtonLeftTest : public UTest::TestBase
{
public:
	ButtonLeftTest() :
			TestBase("ButtonLeftTest")
	{
	}

	void test() override
	{
		ButtonsModule* module = getButtonsModule();

		// Manual test of button
		while(!module->wasButtonPressedLastUpdate(ButtonsModule::ButtonLeft))
		{
		}

		while(!module->wasButtonReleasedLastUpdate(ButtonsModule::ButtonLeft))
		{
		}
	}
};

class ButtonRightTest : public UTest::TestBase
{
public:
	ButtonRightTest() :
			TestBase("ButtonRightTest")
	{
	}

	void test() override
	{
		ButtonsModule* module = getButtonsModule();

		// Manual test of button
		while(!module->wasButtonPressedLastUpdate(ButtonsModule::ButtonRight))
		{
		}

		while(!module->wasButtonReleasedLastUpdate(ButtonsModule::ButtonRight))
		{
		}
	}
};

class ButtonUpTest : public UTest::TestBase
{
public:
	ButtonUpTest() :
			TestBase("ButtonUpTest")
	{
	}

	void test() override
	{
		ButtonsModule* module = getButtonsModule();

		// Manual test of button
		while(!module->wasButtonPressedLastUpdate(ButtonsModule::ButtonUp))
		{
		}

		while(!module->wasButtonReleasedLastUpdate(ButtonsModule::ButtonUp))
		{
		}
	}
};

class ButtonDownTest : public UTest::TestBase
{
public:
	ButtonDownTest() :
			TestBase("ButtonDownTest")
	{
	}

	void test() override
	{
		ButtonsModule* module = getButtonsModule();

		// Manual test of button
		while(!module->wasButtonPressedLastUpdate(ButtonsModule::ButtonDown))
		{
		}

		while(!module->wasButtonReleasedLastUpdate(ButtonsModule::ButtonDown))
		{
		}
	}
};

class ButtonFwdTest : public UTest::TestBase
{
public:
	ButtonFwdTest() :
			TestBase("ButtonFwdTest")
	{
	}

	void test() override
	{
		ButtonsModule* module = getButtonsModule();

		// Manual test of button
		while(!module->wasButtonPressedLastUpdate(ButtonsModule::ButtonForward))
		{
		}

		while(!module->wasButtonReleasedLastUpdate(ButtonsModule::ButtonForward))
		{
		}
	}
};

class ButtonBwdTest : public UTest::TestBase
{
public:
	ButtonBwdTest() :
			TestBase("ButtonBwdTest")
	{
	}

	void test() override
	{
		ButtonsModule* module = getButtonsModule();

		// Manual test of button
		while(!module->wasButtonPressedLastUpdate(ButtonsModule::ButtonBackward))
		{
		}

		while(!module->wasButtonReleasedLastUpdate(ButtonsModule::ButtonBackward))
		{
		}
	}
};

ButtonsTestGroup::ButtonsTestGroup() :
		TestGroup("ButtonsTestGroup")
{
	ADD_TEST(ButtonUpTest);
	ADD_TEST(ButtonDownTest);
	ADD_TEST(ButtonLeftTest);
	ADD_TEST(ButtonRightTest);
	ADD_TEST(ButtonFwdTest);
	ADD_TEST(ButtonBwdTest);

	setIsEndOnFail(false);
}

void ButtonsTestGroup::init()
{
	Pin::initGPIO();
	wait(Milisecond(10));

	static ButtonsModule module;
	ModuleManager::getModuleManager().registerModule(&module);
}

void ButtonsTestGroup::deinit()
{

}

