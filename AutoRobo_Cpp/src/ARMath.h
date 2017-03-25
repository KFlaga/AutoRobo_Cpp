/*
 * ARMath.h
 *
 *  Created on: Mar 21, 2017
 *      Author: Kamil
 */

#ifndef ARMATH_H_
#define ARMATH_H_

#include <type_traits>
#include <math.h>

namespace AutoRobo
{
	// 'Arg' is const T for small PODs and const T& for larger PODs / non-trivial objects
	template<typename T>
	using Arg = typename std::conditional< (sizeof(T) > sizeof(double) && std::is_pod<T>::value),
			typename std::add_const<typename std::add_lvalue_reference<T>::type>::type,
			typename std::add_const<T>::type>::type;

	template<typename T>
	constexpr T max(const T a, const T b)
	{
		return (a) > (b) ? (a) : (b);
	}

	template<typename T>
	constexpr T min(const T a, const T b)
	{
		return (a) < (b) ? (a) : (b);
	}

	template<typename T>
	constexpr T abs(const T a)
	{
		return (a) > 0 ? (a) : -(a);
	}

	constexpr float pi = 3.1416f;

	constexpr float degreeToRadian(const float angleDeg)
	{
		return angleDeg * 0.01745f;
	}

	constexpr float radianToDegree(const float angleRad)
	{
		return angleRad * 57.296f;
	}
}

#endif /* ARMATH_H_ */
