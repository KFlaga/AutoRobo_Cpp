/*
 * MathTests.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: Kamil
 */

#include "TestsPreReqs.h"
#include "TestGroups.h"
#include "ARMath.h"
#include "ARVector2.h"

using namespace AutoRobo;

class RotateVector2Test : public UTest::TestBase
{
public:
	RotateVector2Test() :
			TestBase("RotateVector2Test")
	{
	}

	void test() override
	{
		// Create 30deg vector, rotate by 30 deg
		Vector2 v = Vector2((float)sqrt(3.0), 1.0f);
		Vector2 v2 = v.rotated(degreeToRadian(30.f));
		//Vector2 diff = v2 - Vector2(1.0f, (float)sqrt(3.0));
		//volatile float err2 = diff.lengthSquared();

		assertTrue(v2 == Vector2(1.0f, (float)sqrt(3.0)));
	}
};

class AngleToVector2Q1Test : public UTest::TestBase
{
public:
	AngleToVector2Q1Test() :
			TestBase("AngleToVector2Q1Test")
	{
	}

	void test() override
	{
		// Create 30deg vector, rotate by 30 deg, check if angle is 30 deg
		Vector2 v = Vector2((float)sqrt(3.0), 1.0f).normalized();
		Vector2 v2 = v.rotated(degreeToRadian(30.f));

		assertTrue(AutoRobo::abs(v.angleTo(v2) - degreeToRadian(30.f)) < degreeToRadian(0.1f));
		assertTrue(AutoRobo::abs(v2.angleTo(v) - degreeToRadian(-30.f)) < degreeToRadian(0.1f));
	}
};

class AngleToVector2Q2Test : public UTest::TestBase
{
public:
	AngleToVector2Q2Test() :
			TestBase("AngleToVector2Q2Test")
	{
	}

	void test() override
	{
		// Create 150deg vector, rotate by -30 deg, check if angle is -30 deg
		Vector2 v = Vector2(-(float)sqrt(3.0), 1.0f);
		Vector2 v2 = v.rotated(degreeToRadian(-30.f));

		assertTrue(AutoRobo::abs(v.angleTo(v2) - degreeToRadian(-30.f)) < degreeToRadian(0.1f));
		assertTrue(AutoRobo::abs(v2.angleTo(v) - degreeToRadian(30.f)) < degreeToRadian(0.1f));
	}
};

MathTestGroup::MathTestGroup() :
		TestGroup("MathTestGroup")
{
	ADD_TEST(RotateVector2Test);
	ADD_TEST(AngleToVector2Q1Test);
	ADD_TEST(AngleToVector2Q2Test);

	setIsEndOnFail(false);
}

void MathTestGroup::init()
{

}

void MathTestGroup::deinit()
{

}

