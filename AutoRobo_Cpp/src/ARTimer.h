/*
 * ARTimer.h
 *
 *  Created on: Mar 24, 2017
 *      Author: Kamil
 */

#ifndef ARTIMER_H_
#define ARTIMER_H_

#include "ARTimeSpan.h"
#include <functional>
#include "stm32f4xx.h"

namespace AutoRobo
{
	// High level interface for timers TIMx
	// For now only provides basic functionality :
	// - setting tick interval and callback on single channel
	// - only timers 2,3,4 are supported, for other ids returns non-working dummy timer
	// Intended for repetitive tasks that runs for long time
	// (have lower priority than SystemTimer)
	class Timer
	{
	public:
		static Timer* getTimer(int timerId);

	private:
		std::function<void(TimeSpan)> _callback;
		TimeSpan _interval;
		TimeSpan _tickLength;
		TIM_TypeDef* _timerStruct;

	private:
		// Creates timer based on TIMx, where x is 'timerId'
		Timer(int timerId);

		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

	public:
		// Starts timer and calls 'callback' repeatedly after each 'interval'
		// 'callback' have TimeSpan argument with actual time passed since last call
		// Interval must be less than 60 secs, otherwise timer won't start
		void start(std::function<void(TimeSpan)> callback, TimeSpan interval);
		void stop();

		bool isRunning() const;

		// Should be called from TIMx_IRQHandler
		void update();

		// Returns time since last 'update' (works only if timer is running)
		TimeSpan getCurrentTime() const;
	};
}

#endif /* ARTIMER_H_ */
