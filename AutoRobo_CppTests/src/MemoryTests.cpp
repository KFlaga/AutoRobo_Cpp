//#include "Memory.h"
//#include "TestsPreReqs.h"
//#include "TestGroups.h"
//
//using namespace AutoRobo;
//
//class TestObject
//{
//	int _num;
//	int* _ptr;
//
//public:
//	TestObject(int c)
//	{
//		_num = c;
//		_ptr = MemAllocator::getAllocator()->alloc<int>();
//		*_ptr = c;
//	}
//
//	~TestObject()
//	{
//		*_ptr = 0;
//		MemAllocator::getAllocator()->free<int>(_ptr);
//		_ptr = 0;
//	}
//
//	int getNum()
//	{
//		return _num;
//	}
//
//	int* getPtr()
//	{
//		return _ptr;
//	}
//
//	int getPtrVal()
//	{
//		return *_ptr;
//	}
//};
//
//class AllocAPointerTest : public UTest::TestBase
//{
//public:
//	AllocAPointerTest() :
//			TestBase("AllocAPointerTest")
//	{
//	}
//
//	void test() override
//	{
//		int* ptr = MemAllocator::getAllocator()->alloc<int>();
//		assertTrue(ptr > (int*)0);
//
//		if(ptr != 0)
//			MemAllocator::getAllocator()->free(ptr);
//	}
//};
//
//class FreeAPointerTest : public UTest::TestBase
//{
//public:
//	FreeAPointerTest() :
//			TestBase("FreeAPointerTest")
//	{
//	}
//
//	void test() override
//	{
//		int* ptr = MemAllocator::getAllocator()->alloc<int>();
//		MemAllocator::getAllocator()->free(ptr);
//	}
//};
//
//class CreateAnObjectTest : public UTest::TestBase
//{
//public:
//	CreateAnObjectTest() :
//			TestBase("CreateAnObjectTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* ptr = MemAllocator::getAllocator()->create<TestObject>(5);
//		assertTrue(ptr->getNum() == 5);
//
//		MemAllocator::getAllocator()->free(ptr);
//	}
//};
//
//class DestroyAnObjectTest : public UTest::TestBase
//{
//public:
//	DestroyAnObjectTest() :
//			TestBase("DestroyAnObjectTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* ptr = MemAllocator::getAllocator()->create<TestObject>(5);
//
//		int* numPtr = ptr->getPtr();
//		MemAllocator::getAllocator()->destroy(ptr);
//
//		assertTrue(*numPtr == 0);
//	}
//};
//
//class CreateAnObjectsArrayTest : public UTest::TestBase
//{
//public:
//	CreateAnObjectsArrayTest() :
//			TestBase("CreateAnObjectsArrayTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* arr = MemAllocator::getAllocator()->createArray<TestObject,
//				int>(3, 5);
//		assertTrue(arr[1].getNum() == 5);
//	}
//};
//
//class DestroyAnObjectsArrayTest : public UTest::TestBase
//{
//public:
//	DestroyAnObjectsArrayTest() :
//			TestBase("DestroyAnObjectsArrayTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* arr = MemAllocator::getAllocator()->createArray<TestObject,
//				int>(3, 5);
//
//		int* numPtr = arr[0].getPtr();
//		MemAllocator::getAllocator()->destroyArray(arr, 3);
//
//		assertTrue(*numPtr == 0);
//	}
//};
//
//class CreateAnObjectWithNewTest : public UTest::TestBase
//{
//public:
//	CreateAnObjectWithNewTest() :
//			TestBase("CreateAnObjectWithNewTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* ptr = new TestObject { 5 };
//		assertTrue(ptr->getNum() == 5);
//
//		delete ptr;
//	}
//};
//
//class DestroyAnObjectWithDeleteTest : public UTest::TestBase
//{
//public:
//	DestroyAnObjectWithDeleteTest() :
//			TestBase("DestroyAnObjectWithDeleteTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* ptr = new TestObject { 5 };
//
//		int* numPtr = ptr->getPtr();
//		delete ptr;
//
//		assertTrue(*numPtr == 0);
//	}
//};
//
//class CreateAnObjectsArrayWithNewTest : public UTest::TestBase
//{
//public:
//	CreateAnObjectsArrayWithNewTest() :
//			TestBase("CreateAnObjectsArrayWithNewTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* arr = new TestObject[3] { 1, 2, 3 };
//		assertTrue(arr[1].getNum() == 2);
//
//		delete[] arr;
//	}
//};
//
//class DestroyAnObjectsArrayWithDeleteTest : public UTest::TestBase
//{
//public:
//	DestroyAnObjectsArrayWithDeleteTest() :
//			TestBase("DestroyAnObjectsArrayWithDeleteTest")
//	{
//	}
//
//	void test() override
//	{
//		TestObject* arr = new TestObject[3] { 1, 2, 3 };
//
//		int* numPtr = arr[0].getPtr();
//		delete[] arr;
//
//		assertTrue(*numPtr == 0);
//	}
//};
//
//class HeavyTestObject : public TestObject
//{
//	int _arr[100000];
//
//public:
//	HeavyTestObject(int c) :
//			TestObject(c)
//	{
//	}
//};
//
//class AllocTooMuchMemoryTest : public UTest::TestBase
//{
//public:
//	AllocTooMuchMemoryTest() :
//			TestBase("AllocTooMuchMemoryTest")
//	{
//	}
//
//	void test() override
//	{
//		//HeavyTestObject* ptr = MemAllocator::getAllocator()->alloc<
//		//		HeavyTestObject>();
//		//assertTrue(ptr == (HeavyTestObject*)0);
//
//		// TODO: this test HardFaults, malloc does not return NULL if want to alloc too much
//		// well, uncomment this test when custom allocator is provided
//	}
//};
//
//class FreePointerOutOfRangeTest : public UTest::TestBase
//{
//public:
//	FreePointerOutOfRangeTest() :
//			TestBase("FreePointerOutOfRangeTest")
//	{
//	}
//
//	void test() override
//	{
//		// TODO: check for illegality somehow
//		//int* ptr = (int*)((int)userHeapEnd + 0x100);
//		//MemAllocator::getAllocator()->free(ptr);
//	}
//};
//
//class FreePointerNeverAllocatedTest : public UTest::TestBase
//{
//public:
//	FreePointerNeverAllocatedTest() :
//			TestBase("FreePointerNeverAllocatedTest")
//	{
//	}
//
//	void test() override
//	{
//		// TODO: check for illegality somehow
//		//int* ptr = (int*)((int)userHeapStart + 0x100);
//		//MemAllocator::getAllocator()->free(ptr);
//
//	}
//};
//
//class FreePointerDeallocatedTest : public UTest::TestBase
//{
//public:
//	FreePointerDeallocatedTest() :
//			TestBase("FreePointerDeallocatedTest")
//	{
//	}
//
//	void test() override
//	{
//		// TODO: check for illegality somehow
//		//int* ptr = MemAllocator::getAllocator()->alloc<int>();
//		//MemAllocator::getAllocator()->free(ptr);
//		//MemAllocator::getAllocator()->free(ptr);
//	}
//};
//
//class FreePointerMovedTest : public UTest::TestBase
//{
//public:
//	FreePointerMovedTest() :
//			TestBase("FreePointerMovedTest")
//	{
//	}
//
//	void test() override
//	{
//		// TODO: check for illegality somehow
//		//int* ptr = MemAllocator::getAllocator()->allocArray<int>(5);
//		//MemAllocator::getAllocator()->free(&ptr[2]);
//	}
//};
//
//MemoryTestGroup::MemoryTestGroup() :
//		TestGroup("MemoryTestGroup")
//{
//	ADD_TEST(AllocAPointerTest);
//	ADD_TEST(FreeAPointerTest);
//	ADD_TEST(CreateAnObjectTest);
//	ADD_TEST(DestroyAnObjectTest);
//	ADD_TEST(CreateAnObjectsArrayTest);
//	ADD_TEST(DestroyAnObjectsArrayTest);
//	ADD_TEST(CreateAnObjectWithNewTest);
//	ADD_TEST(DestroyAnObjectWithDeleteTest);
//	ADD_TEST(CreateAnObjectsArrayWithNewTest);
//	ADD_TEST(DestroyAnObjectsArrayWithDeleteTest);
//	ADD_TEST(AllocTooMuchMemoryTest);
//	ADD_TEST(FreePointerOutOfRangeTest);
//	ADD_TEST(FreePointerNeverAllocatedTest);
//	ADD_TEST(FreePointerDeallocatedTest);
//	ADD_TEST(FreePointerMovedTest);
//
//	setIsEndOnFail(false);
//}
//
//void MemoryTestGroup::init()
//{
//
//}
//
//void MemoryTestGroup::deinit()
//{
//	// Free all memory
//}
