#ifndef UTILS_H_
#define UTILS_H_

namespace AutoRobo
{
	static const unsigned char arrowUp = '^';
	static const unsigned char arrowDown = 'v';
	static const unsigned char arrowLeft = 0x7F;
	static const unsigned char arrowRight = 0x7E;

	// bool compare_memory(uint8_t* tab1, uint8_t* tab2, uint16_t sizeInBytes); -> use memcmp
	void uint_to_uchar(unsigned long src, unsigned char* dst);

#ifdef _DEBUG
	// Breaks on if condition is 'false'
	// For now just place breakpoint inside definition
	void debugBreakOnFalse(bool condition);

	// Execute some expression in debug only
#define DEBUG_EXPR(expr) expr
#else
	// Does nothing in release mode
	inline void debugCheck(bool condition)
	{}
#define DEBUG_EXPR(expr)
#endif

	typedef unsigned int TypeId;

	template<typename T>
	struct _TypeIdHelper
	{
		static void func()
		{
		}
	};

	template<typename T>
	constexpr TypeId getTypeId()
	{
		return reinterpret_cast<TypeId>(&_TypeIdHelper<T>::func);
	}

	// Simple not_null - does not enforce value to be not null
	// but serves only that argument should not be null and
	// is not checked inside function
	template<typename T>
	using not_null = T;
}

#define STORE_IN_FLASH __attribute__ ((section(".rodata")))
#define CONST const __attribute__ ((section(".rodata")))

#endif
