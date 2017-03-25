#include <ARSystemTimer.h>
#include "TestsPreReqs.h"
#include "TestGroups.h"
#include "ARMath.h"
#include "ARTimeSpan.h"
#include "ARTimer.h"

using namespace AutoRobo;

class TimeSpanOverflowTest : public UTest::TestBase
{
public:
	TimeSpanOverflowTest() :
			TestBase("TimeSpanOverflowTest")
	{
	}

	void test() override
	{
		// Overflowed time span should have max time
		TimeSpan t1(Microsecond(TimeSpan::maxMicroseconds));
		TimeSpan t2(Microsecond(1));
		TimeSpan t3 = t1 + t2;
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
		assertTrue(t3.getMicroseconds().time == TimeSpan::maxMicroseconds);
#endif
	}
};

class TimeSpanUnderflowTest : public UTest::TestBase
{
public:
	TimeSpanUnderflowTest() :
			TestBase("TimeSpanUnderflowTest")
	{
	}

	void test() override
	{
		// Underflowed time span should have 0 time
		TimeSpan t1(Microsecond(TimeSpan::maxMicroseconds - 1));
		TimeSpan t2(Microsecond(TimeSpan::maxMicroseconds));
		TimeSpan t3 = t1 - t2;
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
		assertTrue(t3.getMicroseconds().time == 0);
#endif
	}
};

class SetResolutionTest : public UTest::TestBase
{
public:
	SetResolutionTest() :
			TestBase("SetResolutionTest")
	{
	}

	void test() override
	{
		// Set resolution 1ms
		SystemTimer& timer = SystemTimer::getSystemTimer();
		bool res = timer.setResolution(Milisecond(1u));

		assertTrue(res);
		assertTrue(TimeSpan(Milisecond(1u)) == timer.getResolution());
	}
};

class OneShotTest : public UTest::TestBase
{
public:
	OneShotTest() :
			TestBase("OneShotTest")
	{
	}

	void init()
	{
		SystemTimer::getSystemTimer().setResolution(Milisecond(1u));
	}

	void test() override
	{
		// Register one shot timer for few ms and wait until it will change a flag
		SystemTimer& timer = SystemTimer::getSystemTimer();
		volatile bool flag = false;

		timer.registerOneShotCallback([&flag]()
		{
			flag = true;
		}, Milisecond(10u));

		while(false == flag)
		{
			// Well it is one of fundamental functions,
			// so cannot be tested other way as by debugging
		}
	}
};

class WaitTest : public UTest::TestBase
{
public:
	WaitTest() :
			TestBase("WaitTest")
	{
	}

	void init()
	{
		SystemTimer::getSystemTimer().setResolution(Milisecond(1u));
	}

	void test() override
	{
		// Register one shot timer for few ms and wait until it will change a flag
		SystemTimer& timer = SystemTimer::getSystemTimer();
		volatile bool flag = false;

		timer.registerOneShotCallback([&flag]()
		{
			flag = true;
		}, Milisecond(10u));

		wait(Milisecond(11u));
		assertTrue(flag);
	}
};

class RepeatedCallbackTest : public UTest::TestBase
{
public:
	RepeatedCallbackTest() :
			TestBase("RepeatedCallbackTest")
	{
	}

	void init()
	{
		SystemTimer::getSystemTimer().setResolution(Milisecond(1u));
	}

	void test() override
	{
		// Register one shot timer for few ms and wait until it will change a flag
		SystemTimer& timer = SystemTimer::getSystemTimer();
		volatile int counter = 0;

		TimerId id = timer.registerRepeatedCallback([&counter]()
		{
			++counter;
		}, Milisecond(2u));

		wait(Milisecond(10u));
		assertTrue(counter == 5); // After 10 ms counter should be 5

		timer.unregisterRepeatedCallback(id);

		wait(Milisecond(11u));
		assertTrue(counter == 5); // Here counter should be still be 5 (if not function wasn't unregistered)
	}
};

class Timer3Test : public UTest::TestBase
{
public:
	Timer3Test() :
			TestBase("Timer3Test")
	{
	}

	void test() override
	{
		// Register callback for timer3 to be shot each 10ms
		Timer* timer = Timer::getTimer(3);

		volatile int counter = 0;
		int expected = 0;

		timer->start([&counter](TimeSpan)
		{
			++counter;
		}, Milisecond(10));

		while(counter < 3)
		{
			++expected;
			wait(Milisecond(11u));
			assertTrue(counter == expected);
		}

		timer->stop();
	}
};

class Timer3CurrentTimeTest : public UTest::TestBase
{
public:
	Timer3CurrentTimeTest() :
			TestBase("Timer3CurrentTimeTest")
	{
	}

	void test() override
	{
		// Register callback for timer3 to be shot each 10ms
		Timer* timer = Timer::getTimer(3);

		volatile bool flag = false;

		timer->start([&flag](TimeSpan)
		{
			flag = true;
		}, Milisecond(10));

		wait(Milisecond(15));
		//assertTrue(true == flag);
		assertTrue(Milisecond(5).time == timer->getCurrentTime().getMiliseconds().time);

		timer->stop();
	}
};

TimeTestGroup::TimeTestGroup() :
		TestGroup("TimeTestGroup")
{
	ADD_TEST(TimeSpanOverflowTest);
	ADD_TEST(TimeSpanUnderflowTest);
	ADD_TEST(SetResolutionTest);
	ADD_TEST(OneShotTest);
	ADD_TEST(WaitTest);
	ADD_TEST(RepeatedCallbackTest);
	ADD_TEST(Timer3Test);

	setIsEndOnFail(true);
}

void TimeTestGroup::init()
{

}

void TimeTestGroup::deinit()
{

}

