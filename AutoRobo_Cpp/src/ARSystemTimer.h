/*
 * ARTime.h
 *
 *  Created on: Mar 23, 2017
 *      Author: Kamil
 */

#ifndef ARSYSTEMTIMER_H_
#define ARSYSTEMTIMER_H_

#include "ARTimeSpan.h"
#include <functional>

namespace AutoRobo
{
	typedef unsigned int TimerId;

	// Represents global timer, which works for entire time and enables
	// to register callback which is fired after specified time passed
	// Based on SysTick timer
	class SystemTimer
	{
	public:
		static SystemTimer& getSystemTimer()
		{
			static SystemTimer timer;
			return timer;
		}

	private:
		SystemTimer();

		// disable copying
		SystemTimer(const SystemTimer&) = delete;
		SystemTimer& operator=(const SystemTimer&) = delete;

	public:
		// Returns time of single timer tick
		TimeSpan getResolution();

		// Sets resolution of timer - time of single tick
		bool setResolution(TimeSpan resolution);

		// Registers callback to be called after specified time passed
		// Callback is fired repeatedly until unregistered
		// Returns id which is used for unregistering
		// If interval is not multiply of resolution, callback is fired and
		// refreshed in same time as it would be rounded up to closest multiply.
		// Callbacks are fired in register order, after one-shots
		TimerId registerRepeatedCallback(std::function<void()> callback, TimeSpan interval);

		// Unregisters previously set callback
		// If id is invalid, nothing happens.
		// No callback should be unregistered inside a callback
		void unregisterRepeatedCallback(TimerId id);

		// Registers callback to be called after specified time passed one time
		// If interval is not multiply of resolution, callback is fired and
		// refreshed in same time as it would be rounded up to closest multiply.
		// Callbacks are fired in register order, before repeated-callbacks
		void registerOneShotCallback(std::function<void()> callback, TimeSpan interval);

		// TODO: implement this
		// Checks if there is a callback to be fired (waiting time = 0)
		// Should be called in low-priority loop or irq (if threads are available)
		// void update();

		// Updates callback timers waiting time (for now also fires callbacks)
		// Should be called inside SysTick_Handler
		void updateTick();
	};

	// Blocks for specified TimeSpan (uses one shot on SystemTimer)
	void wait(TimeSpan waitTime);
}

#endif /* ARSYSTEMTIMER_H_ */
