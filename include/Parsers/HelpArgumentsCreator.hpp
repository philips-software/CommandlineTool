#pragma once
#include <map>
#include <string>

#include "Parsers/CommandArgumentsCreator.hpp"
#include "../Input/CommandArguments.hpp"
#include "../Input/HelpCommand.hpp"

namespace CommandlineTool
{
	/*
		Creates help command arguments.
	*/
	class  HelpArgumentsCreator : public CommandArgumentsCreator
	{
	public:
		HelpArgumentsCreator(std::string commandName) {	}

		constexpr static auto Arg_CommandName = "command";

		CommandArguments CreateArguments(std::map<std::string, std::string> arguments) override
		{
			std::string commandName;
			if (ContainsArgument(arguments, Arg_CommandName))
			{
				commandName = arguments.at(Arg_CommandName);
			}
			else
			{
				commandName = "";
			}


			auto params = std::make_shared<HelpParameters>();
			params->CommandNameToDescribe = commandName;

			return { HelpCommand::HelpName, params };
		}

		/*
			Gets a help text for the argument creator - what argument it expects and what are the values.
		*/
		std::string GetHelpText() override
		{
			std::ostringstream output;
			AddArgumentText(output, "command", "Command to describe", false);
			return output.str();
		}

		std::string GetCommandName() override { return HelpCommand::HelpName; }

	};
}