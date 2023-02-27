#pragma once
#include <map>
#include <string>

#include "CommandArgumentsCreator.hpp"
#include "../Input/CommandArguments.hpp"
#include "../Input/ExitCommand.hpp"

namespace CommandlineTool
{
	/*
		Creates exit command arguments
	*/
	class  ExitArgumentsCreator : public CommandArgumentsCreator
	{
	public:
		static constexpr auto DelayArgument = "delay";

		ExitArgumentsCreator() {	}

		CommandArguments CreateArguments(std::map<std::string, std::string> arguments) override
		{
			auto params = std::make_shared< ExitParameters>();

			if (this->ContainsArgument(arguments, DelayArgument))
			{
				auto delayArg = arguments.at(DelayArgument);
				auto delayAsInteger = std::atoi(delayArg.c_str());
				params->DelayBeforeExit = std::chrono::milliseconds(delayAsInteger);
			}

			return { ExitCommand::ExitName , params };
		}

		/*
			Gets a help text for the argument creator - what argument it expects and what are the values.
		*/
		std::string GetHelpText() override
		{
			std::ostringstream out;

			AddArgumentText(out, DelayArgument, "In Milliseconds - Wait syncrhonously before exiting");

			return out.str();
		}

		std::string GetCommandName() override { return ExitCommand::ExitName; }
	};
}