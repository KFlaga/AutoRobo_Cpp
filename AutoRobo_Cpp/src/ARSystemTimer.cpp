///*
// * ARTime.cpp
// *
// *  Created on: Mar 23, 2017
// *      Author: Kamil
// */
//
#include "stm32f4xx.h"
#include <vector>
#include <algorithm>
#include "ARSystemTimer.h"

namespace AutoRobo
{
	struct OneShotTimerCallback
	{
		std::function<void()> callback;
		TimeSpan remainingTime;
	};

	struct RepeatedTimerCallback
	{
		static TimerId nextId; // There should be enough ids in uint for years

		std::function<void()> callback;
		TimeSpan remainingTime;
		TimeSpan baseTime;
		TimerId id;
	};
	TimerId RepeatedTimerCallback::nextId = 0u;

	static TimeSpan timerResolution;
	static std::vector<RepeatedTimerCallback> repeatedCallbacks { };
	static std::vector<OneShotTimerCallback> oneShotCallbacks { };

	SystemTimer::SystemTimer()
	{
		repeatedCallbacks.reserve(16);
		oneShotCallbacks.reserve(16);
	}

	TimeSpan SystemTimer::getResolution()
	{
		return timerResolution;
	}

#define ticksFor1us 6000000.f

	bool SystemTimer::setResolution(TimeSpan resolution)
	{
		if(SysTick_Config(
				(uint32_t)(SystemCoreClock
						/ (ticksFor1us
								/ (float)resolution.getMicroseconds().time))))
		{
			return false;
		}
		timerResolution = resolution;
		return true;
	}

	TimerId SystemTimer::registerRepeatedCallback(
		std::function<void()> callback, TimeSpan interval)
	{
		const TimerId id = RepeatedTimerCallback::nextId++;
		repeatedCallbacks.push_back(RepeatedTimerCallback { callback, interval,
				interval, id });
		return id;
	}

	void SystemTimer::unregisterRepeatedCallback(TimerId id)
	{
		for(auto it = std::begin(repeatedCallbacks);
				it != std::end(repeatedCallbacks); ++it)
		{
			if(it->id == id)
			{
				repeatedCallbacks.erase(it);
				break;
			}
		}
	}

	void SystemTimer::registerOneShotCallback(std::function<void()> callback,
		TimeSpan interval)
	{
		oneShotCallbacks.push_back(OneShotTimerCallback { callback, interval });
	}

	void SystemTimer::updateTick()
	{
		for(auto& callback : oneShotCallbacks)
		{
			callback.remainingTime = callback.remainingTime - timerResolution;
			if(callback.remainingTime.getMicroseconds().time == 0)
			{
				callback.callback();
			}
		}

		for(auto& callback : repeatedCallbacks)
		{
			callback.remainingTime = callback.remainingTime - timerResolution;
			if(callback.remainingTime.getMicroseconds().time == 0)
			{
				callback.callback();
				callback.remainingTime = callback.baseTime;
			}
		}

		oneShotCallbacks.erase(
				std::remove_if(oneShotCallbacks.begin(), oneShotCallbacks.end(),
						[](auto& cb)->bool
						{
							return cb.remainingTime.getMicroseconds().time == 0;
						}), oneShotCallbacks.end());
	}

	void wait(TimeSpan waitTime)
	{
		volatile bool isWaiting = false;
		SystemTimer::getSystemTimer().registerOneShotCallback([&isWaiting]()
		{
			isWaiting = true;
		}, waitTime);
		while(false == isWaiting)
		{
		}
	}
}
