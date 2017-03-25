/*
 * MemLayout.h
 *
 *  Created on: Mar 20, 2017
 *      Author: Kamil
 */

#ifndef TESTSPREREQS_H_
#define TESTSPREREQS_H_

#include <vector>
#include "UTestTestManager.h"
#include <stdio.h>

namespace AutoRobo
{

static const unsigned int ramStart = 0x20000000;
static const unsigned int ramEnd = 0x20018000;
static const unsigned int userHeapStart = 0x20018000;
static const unsigned int userHeapEnd = 0x20018000;
static const unsigned int userHeapSize = 0x0000;

static const int moduleManagerTimerId = 3;

}

#define ADD_TEST(TestClass) static TestClass test##TestClass; \
	addTest(&test##TestClass);

#define DECLARE_TEST_GROUP(groupName) class groupName : public UTest::TestGroup { \
	public: \
	groupName(); \
	void init() override; \
	void deinit() override; \
}

#define ADD_TEST_GROUP(groupName) static groupName testGroup_##groupName


#endif /* TESTSPREREQS_H_ */
