#pragma once
#include <map>
#include <string>

#include "../Input/CommandArguments.hpp"
#include <sstream>
#include <iomanip>

namespace CommandlineTool
{
	/*
		A Base class for all command parsers.
		It creates a CommandArguments structure and deal with a specific CommandParameter derived class.
	*/
	class  CommandArgumentsCreator
	{
	public:
		/*
			Outputs a CommandArguments for key-value arguments.
		*/
		virtual CommandArguments CreateArguments(std::map<std::string, std::string> arguments) = 0;

		/*
			Gets a help text for the argument creator - what argument it expects and what are the values.
			Help text is in the arguments creator because it only knows what text it parses and what encoding/format it is.
		*/
		virtual std::string GetHelpText() { return ""; }

		/*
			Gets the name of the command it parses arguments for.
		*/
		virtual std::string GetCommandName() { return ""; }

	protected:
		inline bool ContainsArgument(std::map<std::string, std::string> arguments, std::string name)
		{
			return arguments.find(name) != arguments.end();
		}

		void AddArgumentText(std::ostringstream& output, std::string argument, std::string description, bool optional = true)
		{
			auto optionalText = optional ? "Optional" : "Must";
			output << std::setw(40) << std::left << argument << "[ " << std::setw(10) << std::left << optionalText << "] : " << std::setw(60) << std::left << description << "\n";
		}
	};
}