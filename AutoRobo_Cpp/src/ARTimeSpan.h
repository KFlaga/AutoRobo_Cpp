/*
 * ARTimers.h
 *
 *  Created on: Mar 23, 2017
 *      Author: Kamil
 */

#ifndef ARTIMERS_H_
#define ARTIMERS_H_

// #include "stm32f4xx.h"
#include "ARUtils.h"
#include "ARMath.h"

#define DISABLE_TIMESPAN_RANGE_CHECKS 1

namespace AutoRobo
{
	struct Microsecond
	{
		unsigned int time;
		constexpr Microsecond(unsigned int us = 0u) :
				time(us)
		{
		}
	};

	struct Milisecond
	{
		unsigned int time;
		constexpr Milisecond(unsigned int ms = 0u) :
				time(ms)
		{
		}
	};

	struct Second
	{
		unsigned int time;
		constexpr Second(unsigned int s = 0u) :
				time(s)
		{
		}
	};

	// Class representing some time span with unified units
	// May be used for spans up to an hour
	class TimeSpan
	{
	public:
		static const unsigned int maxMicroseconds = ((unsigned int)-2);
		static const unsigned int halfMaxMicroseconds = maxMicroseconds / 2u;
		static const unsigned int maxMiliseconds = maxMicroseconds / 1000u;
		static const unsigned int maxSeconds = maxMiliseconds / 1000u;

	private:
		unsigned int _us;

	public:
		constexpr TimeSpan() :
				_us(0u)
		{
		}

		constexpr TimeSpan(Microsecond us) :
				_us(us.time)
		{
		}

		// 'ms' should be smaller than 'maxMiliseconds'
		// otherwise TimeSpan is overflowed
		constexpr TimeSpan(Milisecond ms) :
				_us(ms.time * 1000u)
		{

		}

		// 's' should be smaller than 'maxSeconds'
		// otherwise TimeSpan is overflowed
		constexpr TimeSpan(Second s) :
				_us(s.time * 1000000u)
		{

		}

		constexpr Microsecond getMicroseconds() const
		{
			return Microsecond(_us);
		}

		constexpr Milisecond getMiliseconds() const
		{
			return Milisecond(_us / 1000u);
		}

		constexpr Second getSeconds() const
		{
			return Second(_us / 1000000u);
		}

		void setMicroseconds(Microsecond us)
		{
			_us = us.time;
		}

		void setMicroseconds(unsigned int us)
		{
			_us = us;
		}

		// 'ms' should be smaller than 'maxMiliseconds'
		// otherwise time span in milliseconds is equal to maxMiliseconds
		void setMiliseconds(Milisecond ms)
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			ms.time = AutoRobo::min(ms.time, maxMiliseconds);
#endif
			_us = ms.time * 1000u;
		}

		// 'ms' should be smaller than 'maxMiliseconds'
		// otherwise time span in milliseconds is equal to maxMiliseconds
		void setMiliseconds(unsigned int ms)
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			ms = AutoRobo::min(ms, maxMiliseconds);
#endif
			_us = ms * 1000u;
		}

		// 's' should be smaller than 'maxSeconds'
		// otherwise time span in seconds is equal to maxSeconds
		void setSeconds(Second s)
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			s.time = AutoRobo::min(s.time, maxSeconds);
#endif
			_us = s.time * 1000000u;
		}

		// 's' should be smaller than 'maxSeconds'
		// otherwise time span in seconds is equal to maxSeconds
		void setSeconds(unsigned int s)
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			s = AutoRobo::min(s, maxSeconds);
#endif
			_us = s * 1000000u;
		}

		constexpr bool operator==(const TimeSpan other) const
		{
			return other._us == _us;
		}

		constexpr bool operator!=(const TimeSpan other) const
		{
			return other._us != _us;
		}

		constexpr bool operator>(const TimeSpan other) const
		{
			return other._us > _us;
		}

		constexpr bool operator<(const TimeSpan other) const
		{
			return other._us < _us;
		}

		// Returns TimeSpan with duration being sum of 2 TimeSpans
		// If summed duration is longer than maximum it is set to maximum
		constexpr TimeSpan operator+(const TimeSpan other) const
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			return ((_us >> 1) + (other._us >> 1)) >= halfMaxMicroseconds ?
			TimeSpan(Microsecond(maxMicroseconds)) :
			TimeSpan(Microsecond(_us + other._us));
#else
			return TimeSpan(Microsecond(_us + other._us));
#endif
		}

		// Returns TimeSpan with duration being difference of 2 TimeSpans
		// If diff duration lower than 0 it is set to 0
		constexpr TimeSpan operator-(const TimeSpan other) const
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			return _us < other._us ?
			TimeSpan() : TimeSpan(Microsecond(_us - other._us));
#else
			return TimeSpan(Microsecond(_us - other._us));
#endif
		}

		// Returns TimeSpan with duration being multiply of this span and multiplier
		// Does not do any checking
		constexpr TimeSpan operator*(const unsigned int m) const
		{
#ifndef DISABLE_TIMESPAN_RANGE_CHECKS
			return (_us == 0 || m == 0) ? TimeSpan() :
			(maxMicroseconds / m) <= _us ?
			TimeSpan(Microsecond(maxMicroseconds)) :
			TimeSpan(Microsecond(_us * m));
#else
			return TimeSpan(Microsecond(_us * m));
#endif
		}
	};
}

#endif /* ARTIMERS_H_ */
