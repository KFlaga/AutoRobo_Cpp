/*
 * ARTimer.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: Kamil
 */

#include "ARTimer.h"
#include "stm32f4xx_tim.h"

#define TIMER_TICKS_PER_US 21
#define TIMER_TICKS_PER_MS 21000

namespace AutoRobo
{
	Timer* Timer::getTimer(int timerId)
	{
		static Timer badTimer(0);
		static Timer timer2(2);
		static Timer timer3(3);
		static Timer timer4(4);
		static Timer* timers[3] = { &timer2, &timer3, &timer4 };

		return (timerId < 2 || timerId > 4) ? &badTimer : timers[timerId - 2];
	}

	Timer::Timer(int timerId)
	{
		switch(timerId)
		{
			case 2 :
				_timerStruct = TIM2;
				RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
				NVIC_EnableIRQ(TIM2_IRQn);
				break;
			case 3 :
				_timerStruct = TIM3;
				RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
				NVIC_EnableIRQ(TIM3_IRQn);
				break;
			case 4 :
				_timerStruct = TIM4;
				RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
				NVIC_EnableIRQ(TIM4_IRQn);
				break;
			default:
				_timerStruct = 0;
				break;
		}

		if(_timerStruct != 0)
		{
			// Init timer
			// Enable CC1 interrupt
			_timerStruct->DIER = 0x0002;
			// Set CC1 as output
			_timerStruct->CCER = 0x0001;
		}
	}

	void Timer::start(std::function<void(TimeSpan)> callback, TimeSpan interval)
	{
		if(_timerStruct == 0)
			return;

		// 84Mhz MCU -> 1/4 on APB1 = 21Mhz, so 21 ticks each us
		if(interval < TimeSpan(Microsecond(1000)))
		{
			// If interval is 1us-1000us:
			// set PSC so that tick is 1us -> 20 (21 ticks for us -1)
			// set AAR so that end is on twice the interval : int_us * 2
			// set CCR1 so that interrupt is on the interval : int_us
			_tickLength = Microsecond(1);
			_timerStruct->PSC = (TIMER_TICKS_PER_US - 1);
			_timerStruct->ARR = interval.getMicroseconds().time * 2u;
			_timerStruct->CCR1 = interval.getMicroseconds().time;
		}
		else if(interval < TimeSpan(Milisecond(1000)))
		{
			// If interval is 1ms-1000ms:
			// set PSC so that tick is 0.1ms -> 2099
			// set AAR so that end is on twice the interval : int_ms * 20 + (int_us/100)*2
			// set CCR1 so that interrupt is on the interval : int_ms * 10 + (int_us/100)
			_tickLength = Microsecond(100);
			_timerStruct->PSC = (TIMER_TICKS_PER_US * 100 - 1);
			_timerStruct->ARR = interval.getMiliseconds().time * 20u
					+ interval.getMicroseconds().time / 50;
			_timerStruct->CCR1 = interval.getMiliseconds().time * 10u
					+ interval.getMicroseconds().time / 100;
		}
		else if(interval < TimeSpan(Second(61)))
		{
			// If interval is > 1s
			// set PSC so that tick is 2ms -> 41999
			// set AAR so that end is on twice the interval : int_s * 1000 + int_ms
			// set CCR1 so that interrupt is on the interval : int_s * 500 + int_ms/2
			// As max ARR is 65536, then max interval is ~65secs
			_tickLength = Milisecond(2);
			_timerStruct->PSC = (TIMER_TICKS_PER_MS * 2 - 1);
			_timerStruct->ARR = interval.getSeconds().time * 1000u
					+ interval.getMiliseconds().time;
			_timerStruct->CCR1 = interval.getSeconds().time * 500u
					+ interval.getMiliseconds().time / 2;
		}
		else
		{
			_tickLength = Microsecond(0);
			return;
		}

		_callback = callback;
		_interval = interval;

		_timerStruct->CNT = 0;
		_timerStruct->CR1 |= 1;
	}

	void Timer::stop()
	{
		_timerStruct->CR1 &= 0xFFFE;
		_callback = std::function<void(TimeSpan)>();
		_tickLength = Microsecond(0);
	}

	void Timer::update()
	{
		if(_timerStruct->SR & TIM_SR_CC1IF)
		{
			TimeSpan t = getCurrentTime();
			if(_callback)
			{
				_callback(t);
			}
			_timerStruct->CNT = 0;
		}
		_timerStruct->SR = 0;
	}

	bool Timer::isRunning() const
	{
		return _tickLength.getMicroseconds().time > 0;
	}

	TimeSpan Timer::getCurrentTime() const
	{
		// read CNT -> it is reset on each update
		return _tickLength * _timerStruct->CNT;
	}
}

