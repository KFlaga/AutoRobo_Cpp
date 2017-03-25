/*
 * PinsTests.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: Kamil
 */

#include "TestsPreReqs.h"
#include "TestGroups.h"
#include "ARPins.h"
#include "ARSystemTimer.h"

using namespace AutoRobo;

class PinOutputTest : public UTest::TestBase
{
public:
	PinOutputTest() :
			TestBase("PinOutputTest")
	{
	}

	void test() override
	{
		// Set pin for in-board LED as output and set it high/low
		// (well to check if input/output config works manual test is needed)
		Pin ledPin(GPIOA, 5);
		ledPin.setAsOutput();
		ledPin.setPushUp();
		wait(Milisecond(10));
		ledPin.setHigh();
		wait(Second(1));
		ledPin.setLow();
		wait(Second(1));
		ledPin.setHigh();
		wait(Second(1));
		ledPin.setLow();
	}
};

class PinInputTest : public UTest::TestBase
{
public:
	PinInputTest() :
			TestBase("PinInputTest")
	{
	}

	void test() override
	{
		// Set pin for in-board button as input and check if it changes state
		// (well to check if input/output config works manual test is needed)
		Pin buttonPin(GPIOC, 13);
		buttonPin.setAsOutput();
		buttonPin.setPushUp();
		wait(Milisecond(10));

		while(buttonPin.isHigh())
		{
			wait(Milisecond(100));
		}

		while(buttonPin.isLow())
		{
			wait(Milisecond(100));
		}
	}
};

PinsTestGroup::PinsTestGroup() :
		TestGroup("PinsTestGroup")
{
	ADD_TEST(PinOutputTest);
	ADD_TEST(PinInputTest);

	setIsEndOnFail(false);
}

void PinsTestGroup::init()
{
	Pin::initGPIO();
	wait(Milisecond(10));
}

void PinsTestGroup::deinit()
{

}
