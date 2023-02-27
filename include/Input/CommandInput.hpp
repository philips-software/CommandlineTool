#pragma once

#include "CommandArguments.hpp"

namespace CommandlineTool
{
	/*
	Base class for input units to get a description of a command. (CommandArguments)
	*/
	class CommandInput
	{

	public:
		/*
		Inputs from a source command arguments.
		*/
		virtual CommandArguments OnInput() = 0;
	};
}