#include "Memory.h"
#include <stdlib.h>

using namespace AutoRobo;

MemAllocator* MemAllocator::_allocator = nullptr;
size_t _freePtr;

void MemAllocator::initAllocator(unsigned int heapStart, unsigned int heapSize)
{
	static MemAllocator allocator(heapStart, heapSize);
	_allocator = &allocator;
}

//void* operator new(std::size_t n) throw (std::bad_alloc)
//{
//	return MemAllocator::getAllocator()->alloc(n);
//}
//
//void operator delete(void* p) throw ()
//{
//	MemAllocator::getAllocator()->free(p);
//}

MemAllocator::MemAllocator(size_t heapStart, size_t heapSize) :
		_heapStart(heapStart),
		_heapSize(heapSize),
		_maxSize(heapSize / 2)
{
	_freePtr = _heapStart;
}

void MemAllocator::resetMemory()
{
	_freePtr = _heapStart;
}

//#define FOOTPRINT_SIZE sizeof(size_t)

void* MemAllocator::alloc(size_t size)
{
	void* ptr = ::malloc(size);
	return ptr;
}

void MemAllocator::free(void* ptr)
{
	::free(ptr);
}
