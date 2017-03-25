#ifndef UTESTTESTBASE_H_
#define UTESTTESTBASE_H_

namespace UTest
{

/*
 * Base class for unit tests.
 *
 * To create new test, subclass TestBase and override 'test' method.
 * Tests should be created and added in TestGroup constructors only and
 * run from within those groups.
 *
 * Tests allow for state checking with 'assertXXX' methods.
 * Before 'test' method is called, test result is set to 'Passed' and if
 * any of checks is unsuccessful then it is changed to 'Failed'.
 *
 * As 'UTest' it is intended to be run without exception support
 * unsuccessful asserts does not break test, so if it is necessary then after
 * each 'assertXXX' test result should be checked.
 *
 * Subclasses may override 'init' and 'deinit' methods which are called
 * before first and after test is run.
 *
 * TODO: add custom fail message support
 * TODO: add exit test after assertion failed (i.e. using jump)
 */
class TestBase
{
public:
	enum class TestResult : unsigned char
	{
		NotRun = 0,
		Passed,
		Failed
	};

protected:
	const char* _testName;
	TestResult _testResult;

protected:
	TestBase(const char* testName);

public:
	virtual ~TestBase();

	void run();

	virtual void test() = 0;
	virtual void init();
	virtual void deinit();

	TestResult getResult() const { return _testResult; }
	const char* getName() const { return _testName; }

protected:
	// Checks if condition is 'true' and sets test result as 'false' if not
	void assertTrue(bool condition);

	// Checks if condition is 'false' and sets test result as 'false' if not
	void assertFalse(bool condition);

	template<typename T>
	using CheckFunc1 = bool(*)(const T&);

	template<typename T1, typename T2>
	using CheckFunc2 = bool(*)(const T1&, const T2&);

	// Checks if both passed objects are equal (using '==' operator)
	template<typename T1, typename T2>
	void assertEquals(const T1& a, const T2& b)
	{
		assertTrue(a == b);
	}

	// Checks if both passed objects are not equal (using '!=' operator)
	template<typename T1, typename T2>
	void assertNotEquals(const T1& a, const T2& b)
	{
		assertTrue(a != b);
	}

	// Checks if passed objects pass supplied check function
	template<typename T1, typename T2>
	void assertCheck2Passes(const T1& obj1, const T2& obj2,
			CheckFunc2<T1, T2> check)
	{
		assertTrue(check(obj1, obj2));
	}

	// Checks if passed objects fail supplied check function
	template<typename T1, typename T2>
	void assertCheck2Fails(const T1& obj1, const T2& obj2,
			CheckFunc2<T1, T2> check)
	{
		assertFalse(check(obj1, obj2));
	}

	// Checks if passed object passes supplied check function
	template<typename T1>
	void assertCheck1Passes(const T1& obj1, CheckFunc1<T1> check)
	{
		assertTrue(check(obj1));
	}

	// Checks if passed object fails supplied check function
	template<typename T1>
	void assertCheck1Fails(const T1& obj1, CheckFunc1<T1> check)
	{
		assertFalse(check(obj1));
	}

	// Checks if all bits set in 'mask' are also set in 'flags'
	void assertBitsSet(unsigned int flags, unsigned int mask);

	// Checks if all bits set in 'mask' are reset in 'flags'
	void assertBitsReset(unsigned int flags, unsigned int mask);
};
}

#endif /* UTESTTESTBASE_H_ */
