
#ifndef MOVEMENT_ARROBOPROGRAMSTORAGE_H_
#define MOVEMENT_ARROBOPROGRAMSTORAGE_H_

#include "ARRoboProgram.h"
#include "../ARUtils.h"

namespace AutoRobo
{
	class RoboProgramStorage
	{
	public:
		RoboProgramStorage(uint8_t initialCapacity);

		RoboProgram* getProgramById(uint8_t progId);
		RoboProgram* getProgramByName(uint8_t* progName);

		const std::vector<RoboProgram*>& getProgramList() const;

		// Adds program to storage. Sets its id
		void addProgram(RoboProgram*);
		// Removes program - if there's no such program nothing happens
		void removeProgram(RoboProgram*);
		// Removes program - if there's no such program nothing happens
		void removeProgram(uint8_t programId);
	};
}

#endif /* MOVEMENT_ARROBOPROGRAMSTORAGE_H_ */
