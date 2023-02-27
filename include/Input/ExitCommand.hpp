#pragma once

#include "Command.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace CommandlineTool
{
	class ExitParameters : public CommandParameters
	{
	public:
		std::chrono::milliseconds DelayBeforeExit = std::chrono::milliseconds(0);
	};

	/*
		A Command that does nothing and should affect the exit of the command executioner by default behavior.
	*/
	class ExitCommand : public Command
	{
	public:
		void Execute(const CommandArguments &args) override
		{
			auto exitParams = std::dynamic_pointer_cast<ExitParameters>(args.GetParameters());
			std::this_thread::sleep_for(exitParams->DelayBeforeExit);
			std::cout << "Exiting..." << std::endl;
			std::exit(0);
		}

		std::string GetName() override { return ExitName; }

		static const std::string ExitName;
	};

	const std::string ExitCommand::ExitName = "exit";
}