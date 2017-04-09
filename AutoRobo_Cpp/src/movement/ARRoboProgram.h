/*
 * ARRoboProgram.h
 *
 *  Created on: Apr 7, 2017
 *      Author: Kamil
 */

#ifndef MOVEMENT_ARROBOPROGRAM_H_
#define MOVEMENT_ARROBOPROGRAM_H_

#include <vector>

namespace AutoRobo
{
	enum class RoboFunctionType
	{
		Null = 0x0, Wait = 0x1, // Instruction is wait-function
		Movement = 0x200, // Instruction is movement-function
		MoveLine = RoboFunction_Movement | 0x2,
		Rotate = RoboFunction_Movement | 0x3,
		MoveArc = RoboFunction_Movement | 0x4,
		MoveToPoint = RoboFunction_Movement | 0x5,
		ResetSensors = 0x6,

		FunctionsCount = 7,
	};

	/**
	 * Contains definition of a robot function.
	 * Instructions share common definition.
	 * Defines:
	 * - name to display
	 * - parameters (up to 3) : names, default values, steps
	 */
	struct RoboFunctionDefinition
	{
		const RoboFunctionType function; // Function type to actually execute
		const uint8_t name[9]; // Short name of function to display
		const uint8_t paramNames[3]; // Names of parameters to display
		const uint8_t paramUnits[6]; // Units of parameters to display
		const uint8_t paramCount; // Number of parameters used in this function (up to 3)
		const int16_t paramDefaultVals[3]; // Default values of parameters
		const int8_t paramIncrement[3]; // Change in parameters value for one button-press

		// Returns 'RoboFunctionDefinition' with given type
		static RoboFunctionDefinition* getDefintion(RoboFunctionType type);
		// Sets 'RoboFunctionDefinition' for given type
		static void setDefintion(RoboFunctionType type, RoboFunctionDefinition* def);
		// Returns array with all 'RoboFunctionDefinition's (with count = RoboFunctionType::FunctionsCount)
		static RoboFunctionDefinition** getAllDefintions();
	};

	/**
	 * Instruction to execute single function with
	 * given parameters.
	 */
	struct RoboInstruction
	{
		RoboFunctionDefinition* definition;
		int16_t params[3]; // Actual parameters' values
		uint8_t steering; // MovementAlgorithm to use
	};

	/**
	 * Program containing multiple instruction to be executed in sequence.
	 */
	struct RoboProgram
	{
		std::vector<RoboInstruction> instructions;
		uint8_t name[13]; // max len = 12
		uint8_t curInstr;
		uint8_t id;
	};
}

#endif /* MOVEMENT_ARROBOPROGRAM_H_ */
