/*
 * Memory.h
 *
 *  Created on: Mar 19, 2017
 *      Author: Kamil
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <new>

namespace AutoRobo
{
	typedef std::size_t size_t;


	// Dynamic memory allocator intended to use on user heap
	// (specified in memory layout)
	// For now just wraps malloc/free
	// Later will override global new/delete operators
	class MemAllocator
	{
	protected:
		static MemAllocator* _allocator;

		size_t _heapStart;
		size_t _heapSize;
		size_t _maxSize;
		MemAllocator(size_t heapStart, size_t heapSize);

	public:
		static void initAllocator(unsigned int heapStart,
			unsigned int heapSize);
		static MemAllocator* getAllocator()
		{
			return _allocator;
		}

	public:
		template<typename T, typename ... Args>
		T* create(Args ... args)
		{
			T* obj = alloc<T>();
			new (obj) T { args... };
			return obj;
		}

		template<typename T, typename ... Args>
		T* createArray(unsigned int count, Args ... args)
		{
			T* arr = allocArray<T>(count);
			for(unsigned int i = 0; i < count; ++i)
			{
				new (&arr[i]) T { args... };
			}
			return arr;
		}

		template<typename T>
		void destroy(T* ptr)
		{
			ptr->~T();
			free<T>(ptr);
		}

		template<typename T>
		void destroyArray(T* ptr, unsigned int count)
		{
			for(unsigned int i = 0; i < count; ++i)
			{
				ptr[i].~T();
			}
			free<T>(ptr);
		}

		template<typename T>
		T* alloc()
		{
			return reinterpret_cast<T*>(alloc(sizeof(T)));
		}

		template<typename T>
		T* allocArray(unsigned int count)
		{
			return reinterpret_cast<T*>(alloc(count * sizeof(T)));
		}

		template<typename T>
		void free(T* ptr)
		{
			this->free(reinterpret_cast<void*>(ptr));
		}

		size_t maxSize()
		{
			return _maxSize;
		}

		void resetMemory();

		void* alloc(size_t size);
		void free(void* ptr);
	};

	template<class T>
	struct StdAllocator
	{
		typedef T value_type;
		typedef T* pointer;
		typedef std::size_t size_type;
		typedef int difference_type;

		StdAllocator()
		{
		}

		template<class U>
		StdAllocator(const StdAllocator<U>& other)
		{
		}

		T* allocate(std::size_t n)
		{
			MemAllocator::getAllocator()->allocArray<T>(n);
		}

		void deallocate(T* p, std::size_t n)
		{
			MemAllocator::getAllocator()->free<T>(p);
		}

		size_type max_size()
		{
			return MemAllocator::getAllocator()->maxSize();
		}
	};

}

template<class T, class U>
bool operator==(const AutoRobo::StdAllocator<T>&,
	const AutoRobo::StdAllocator<U>&)
{
	return true;
}

template<class T, class U>
bool operator!=(const AutoRobo::StdAllocator<T>&,
	const AutoRobo::StdAllocator<U>&)
{
	return false;
}

#endif /* MEMORY_H_ */
