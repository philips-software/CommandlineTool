#pragma once

#include <memory>
#include "../libs/cxxopts/cxxopts.hpp"

#include "Executioner.hpp"
#include "OnStartHandler.hpp"
#include "OnFinishHandler.hpp"
#include "Input/OneTimeInput.hpp"
#include "Input/ConsoleInput.hpp"
#include "Input/Command.hpp"
#include "Input/CommandTextInput.hpp"
#include "Input/ExitCommand.hpp"
#include "Input/HelpCommand.hpp"
#include "Parsers/ExitArgumentsCreator.hpp"
#include "Parsers/HelpArgumentsCreator.hpp"
#include "Parsers/ExecutableArgumentsParser.hpp"

namespace CommandlineTool
{
	enum class ProgramExitCode
	{
		ExecutionError = -1,
		ProgramOk = 0,
		ERROR_ProgramValidationFailed
	};

	/*
		Defines a facade interface to a running commandline tool.
	*/
	class Program
	{
	public:
		Program(std::string toolName)
		{
			mStartHandler = std::make_shared<OnStartHandler>();
			mFinishHandler = std::make_shared<OnFinishHandler>();
		}

		virtual ~Program() = default;
		/*
			Registers a command input into the program.
			The command input is used to get the command arguments for execution.
		*/
		Program *ConfigureCommandInput(std::shared_ptr<CommandInput> commandInput)
		{
			mCommandInput = commandInput;
			return this;
		}

		/*
			Register a parser for the executable arguments recieved by the commandline.
		*/
		Program *ConfigureExecutableOptionsParser(std::shared_ptr<ExecutableArgumentsParser> exeOptionsParser)
		{
			mExeOptionsParser = exeOptionsParser;
			return this;
		}

		/*
			Registers into the handling of the recieved commandline options parsed by the ExecutableOptionsParser.
			The user may inherit OnStartHandler and use the commandline options as they want.
		*/
		Program *ConfigureStartHandler(std::shared_ptr<OnStartHandler> startHandler)
		{
			mStartHandler = startHandler;
			return this;
		}

		/*
			Registers an handle for the finalization operations.
		*/
		Program *ConfigureFinishHandler(std::shared_ptr<OnFinishHandler> finishHandler)
		{
			mFinishHandler = finishHandler;
			return this;
		}

		/*
			Register the main logic executioner for commands.
		*/
		Program *ConfigureCommandExecutioner(std::shared_ptr<Executioner> commandExecutioner)
		{
			mCommandExecutioner = commandExecutioner;
			if (mHelpCommand != nullptr)
			{
				mCommandExecutioner->AddCommand(mHelpCommand);
			}
			return this;
		}

		/*
			Configures the program to run with default instances of the engine.
			ConsoleInput is used to get CommandArguments therefore it needs the <map> to parse command parameters.
			ExecutableOptionsParser is used to parse commandline parameters.
			CommandExecutioner is used to execute commands - synchronously.
		*/
		Program *ConfigureDefault(CommandTextInput::ArgumentsFacotryMap map)
		{
			std::string exitName = ExitCommand::ExitName;
			std::string helpName = HelpCommand::HelpName;
			StringHelper::ToUpperCase(exitName);
			StringHelper::ToUpperCase(helpName);
			map.insert({exitName, std::make_shared<ExitArgumentsCreator>()});
			map.insert({helpName, std::make_shared<HelpArgumentsCreator>(HelpCommand::HelpName)});

			mCommandInput = std::make_shared<ConsoleInput>(map);
			mCommandExecutioner = std::make_shared<Executioner>();
			mExeOptionsParser = std::make_shared<ExecutableArgumentsParser>(mToolName);

			mIsDefaultBehaviorUsed = true;

			SetupHelpCommand(map);
			return this;
		}

		/*
			Adds an option to parse from the executable arguments.
		*/
		template <typename TValue>
		Program *ConfigureExecutableOption(std::string rule, std::string description, std::string defaultValue);

		/*
			Adds a command for the running execution engine.
		*/
		Program *ConfigureCommand(std::shared_ptr<Command> commandToAdd)
		{
			mCommandExecutioner->AddCommand(commandToAdd);
			mWasConfigureCommandCalled = true;

			return this;
		}

		/*
			After all the Configuration are done - Runs the Commandline Tool.
		*/
		virtual int Run(int argumentCount, char **arguments)
		{
			if (!ValidateBeforeRun())
			{
				return static_cast<int>(ProgramExitCode::ERROR_ProgramValidationFailed);
			}

			if (mIsDefaultBehaviorUsed)
			{
				std::cout << ("Default behavior is used, Configuration exit, help and one time commands");
				mCommandExecutioner->AddCommand(std::make_unique<ExitCommand>());
				mExeOptionsParser->AddOption(std::string("h,help"), std::string("Shows help text"));
				mExeOptionsParser->AddOption(std::string("one_time_command"), std::string("Executes a command for a single time only"),
											 cxxopts::value<std::string>()->default_value(""));
			}

			std::cout << ("Parsing execution parameters.");

			auto shouldContinue = true;
			auto options = mExeOptionsParser->Parse(argumentCount, arguments, shouldContinue);

			bool isInteractive = true;
			if (options.count("one_time_command") > 0)
			{
				auto &oneTimeCommand = options["one_time_command"].as<std::string>();
				std::cout << ("One time command is: %s", oneTimeCommand.c_str());

				isInteractive = false;
				auto textInput = std::dynamic_pointer_cast<CommandTextInput>(mCommandInput);
				if (textInput != nullptr)
				{
					auto oneTimeInput = std::make_shared<OneTimeInput>((CommandTextInput &)*mCommandInput);
					oneTimeInput->SetCommand(oneTimeCommand);
					mCommandInput = oneTimeInput;
				}
			}

			if (!shouldContinue)
			{
				mFinishHandler->OnFinish();
				return 0;
			}

			if (mStartHandler != nullptr)
			{
				mStartHandler->OnStart(options);
			}

			do
			{
				std::cout << "Enter a command:\n";
				bool success;
				auto commandArgs = TryGetInput(success);
				if (!success)
				{
					std::cerr << ("Couldn't parse input");
					continue;
				}

				mCommandExecutioner->Execute(*commandArgs);
			} while (isInteractive);

			mFinishHandler->OnFinish();

			mCommandInput.reset();
			mExeOptionsParser.reset();
			mStartHandler.reset();
			mCommandExecutioner.reset();

			return static_cast<int>(ProgramExitCode::ProgramOk);
		}

	protected:
		/*
			Validates that all necessary ConfigureXXXX were called before calling Run()
		*/
		bool ValidateBeforeRun()
		{
			if (mExeOptionsParser == nullptr)
			{
				std::cerr << ("Need to call ConfigureExecutableOptionsParser or ConfigureDefault before calling Run()");
				return false;
			}
			if (mCommandInput == nullptr)
			{
				std::cerr << ("Need to call ConfigureCommandInput or ConfigureDefault before calling Run()");
				return false;
			}
			if (mCommandExecutioner == nullptr)
			{
				std::cerr << ("Need to call ConfigureCommandExecutioner or ConfigureDefault before calling Run()");
				return false;
			}
			if (!mWasConfigureCommandCalled)
			{
				std::cerr << ("Commands were not added to the Program! It will work but do nothing...");
			}
			if (!mWasConfigureCommandCalled)
			{
				std::cerr << ("Executable options were not added, it's not mandatory but might be helpful.");
			}
			return true;
		}

		std::shared_ptr<CommandArguments> TryGetInput(bool &success)
		{
			try
			{
				success = true;
				return std::make_shared<CommandArguments>(mCommandInput->OnInput());
			}
			catch (std::exception e)
			{
				std::cerr << (e.what());
				success = false;
				return {};
			}
		}

	private:
		/*
			For default behavior we setup the help command using arguments factory map -> Command name and their Help Text.
		*/
		void SetupHelpCommand(const CommandTextInput::ArgumentsFacotryMap &map)
		{
			mHelpCommand = std::make_shared<HelpCommand>();

			for (auto &factoryMap : map)
			{
				mHelpCommand->AddCommand(factoryMap.second->GetCommandName(), factoryMap.second->GetHelpText());
			}

			mCommandExecutioner->AddCommand(mHelpCommand);
		}

		std::shared_ptr<CommandInput> mCommandInput;
		std::shared_ptr<ExecutableArgumentsParser> mExeOptionsParser;
		std::shared_ptr<OnStartHandler> mStartHandler;
		std::shared_ptr<OnFinishHandler> mFinishHandler;
		std::shared_ptr<Executioner> mCommandExecutioner;
		std::string mToolName;
		std::shared_ptr<HelpCommand> mHelpCommand;

		bool mWasConfigureCommandCalled = false;
		bool mWasExecutableOptionAdded = false;
		bool mIsDefaultBehaviorUsed = false;
	};

	template <typename TValue>
	inline Program *Program::ConfigureExecutableOption(std::string rule, std::string description, std::string defaultValue)
	{
		mExeOptionsParser->AddOption(rule, description, cxxopts::value<TValue>()->default_value(defaultValue));
		mWasExecutableOptionAdded = true;
		return this;
	}
}