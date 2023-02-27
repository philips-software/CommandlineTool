#pragma once

#include "Command.hpp"
#include "HelpCommand.hpp"
#include <map>
#include <string>
#include <sstream>
#include <iostream>

namespace CommandlineTool
{

	class HelpParameters : public CommandParameters
	{
	public:
		std::string CommandNameToDescribe;
	};

	/*
		A Command that does nothing and should affect the exit of the command executioner by default behavior.
	*/
	class HelpCommand : public Command
	{
	public:
		void Execute(const CommandArguments &args) override
		{
			auto helpParams = GetParameters<HelpParameters>(args);

			auto cmdName = helpParams->CommandNameToDescribe;

			std::ostringstream output;
			int width = 60;
			if (cmdName.empty())
			{
				output << "============================================\n";
				output << "Add command=[commandname] to see a specific command\n";
				output << "List of Commands:";
				for (auto &kv : mHelpText)
				{
					output << kv.first << "\n";
				}
				output << "============================================\n";
				std::cout << output.str() << "\n";
				return;
			}

			if (mHelpText.find(cmdName) == mHelpText.end())
			{
				std::cerr << "Help couldnt find command: " << cmdName << "\n";
				return;
			}
			auto helpText = mHelpText.at(cmdName);
			output << "============================================\n";
			output << cmdName << ":\n";
			output << helpText;
			output << "============================================\n";
			std::cout << output.str() << "\n";
		}

		std::string GetName() override { return HelpName; }

		constexpr static auto HelpName = "help";

		void AddCommand(std::string commnadName, std::string helpText)
		{
			mHelpText.insert({commnadName, helpText});
		}

	private:
		std::map<std::string, std::string> mHelpText;
	};

}