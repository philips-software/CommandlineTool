#pragma once

#include "../libs/cxxopts/cxxopts.hpp"

namespace CommandlineTool
{
	/*
		Handles the executable options.
	*/
	class  OnStartHandler
	{
	public:
		/*
			Allows the user to recieve the parsed results for the executable options.
		*/
		virtual void OnStart(cxxopts::ParseResult parsingResult) {}
	};
}