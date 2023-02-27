#pragma once

#include <string>
#include <memory>
#include <map>


#include "Input/Command.hpp"
#include "Input/CommandInput.hpp"
#include "Input/HelpCommand.hpp"

namespace CommandlineTool
{
	/*
		The engine which executes commands by requests of command arguments.
	*/
	class Executioner
	{
	public:
		Executioner() = default;
		Executioner(Executioner& other) = delete;
		Executioner(Executioner&& other) noexcept = default;

		Executioner& operator=(const Executioner& other) = delete;
		Executioner& operator=(Executioner&& other) = default;

		virtual ~Executioner() = default;

		virtual void Execute(const CommandArguments& arguments)
		{
			auto cmdName = arguments.GetCommandName();

			if (mCommands.find(cmdName) == mCommands.end())
			{
				std::cerr << "Couldn't find command " << cmdName << ".\n";
				return;
			}
			mCommands.at(cmdName)->Execute(arguments);
		}

		void AddCommand(std::shared_ptr<Command> command)
		{
			mCommands.try_emplace(command->GetName(), command);
		}

	protected:
		std::map<std::string, std::shared_ptr<Command>> mCommands;
		std::shared_ptr<HelpCommand> mHelpCommand;
	};
}