#pragma once
#include <map>
#include <string>

#include "CommandArguments.hpp"
#include "Parsers/CommandArgumentsCreator.hpp"

namespace CommandlineTool
{
	/*
		Creates an Empty command arguments for commands
		that don't want any arguments.  
	*/
	class  EmptyArgumentsCreator : public CommandArgumentsCreator
	{
	public:
		EmptyArgumentsCreator(std::string commandName, std::string additionalHelpText = "")
			:mCommandName(commandName), mAdditionalText(additionalHelpText) {	}

		CommandArguments CreateArguments(std::map<std::string, std::string> arguments) override
		{
			return { mCommandName,{} };
		}

		/*
			Gets a help text for the argument creator - what argument it expects and what are the values.
		*/
		std::string GetHelpText() override
		{
			return mCommandName + ": " + mAdditionalText;
		}

		std::string GetCommandName() override { return mCommandName; }

	private:
		std::string mCommandName;
		std::string mAdditionalText;
	};
}