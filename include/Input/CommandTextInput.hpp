#pragma once
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <sstream>

#include "CommandInput.hpp"
#include "../Utils/StringHelper.hpp"
#include "../Input/CommandArguments.hpp"
#include "../Parsers/CommandParametersParser.hpp"
#include "../Parsers/CommandArgumentsCreator.hpp"

namespace CommandlineTool
{
	/*
		Outputs a CommandArguments based on a textual input.
	*/
	class CommandTextInput : public CommandInput
	{
	public:
		using ArgumentsFactory = std::shared_ptr<CommandArgumentsCreator>;
		using ArgumentsFacotryMap = std::map<std::string, ArgumentsFactory>;
		const char CommandDelimiter = ' ';

		CommandTextInput(ArgumentsFacotryMap argumentsCreatorMap)
			: mCommandParamParser(std::make_shared<CommandParametersParser>())
		{
			InitFactoryMap(argumentsCreatorMap);
		}

		CommandTextInput(ArgumentsFacotryMap argumentsCreatorMap, std::shared_ptr<CommandParametersParser> parser)
			: mCommandParamParser(parser)
		{
			InitFactoryMap(argumentsCreatorMap);
		}

		CommandTextInput(const CommandTextInput &other) = default;
		CommandTextInput(CommandTextInput &&other) noexcept = default;

		CommandArguments OnInput() final
		{
			auto commandInput = RecieveInput();

			auto nameToParameters = GetCommandNameWithParams(commandInput);
			auto commandName = nameToParameters.first;
			auto commandParams = nameToParameters.second;
			if (commandName == "")
			{
				// TODO: Log and Out.
				return {"", {}};
			}

			StringHelper::ToUpperCase(commandName);

			auto keyValueParameters = mCommandParamParser->Parse(commandParams);

			if (mCommandArgumentsCreator.find(commandName) != mCommandArgumentsCreator.end())
			{
				auto correctCreator = mCommandArgumentsCreator.at(commandName);
				auto commandArgs = correctCreator->CreateArguments(keyValueParameters);
				return commandArgs;
			}

			return {"", {}};
		}

	protected:
		virtual std::string RecieveInput() = 0;

		ArgumentsFacotryMap mCommandArgumentsCreator;
		std::shared_ptr<CommandParametersParser> mCommandParamParser;

		std::pair<std::string, std::string> GetCommandNameWithParams(std::string allInput)
		{
			std::istringstream tokenStream(allInput);

			std::string commandName;
			std::string parameters;

			std::getline(tokenStream, commandName, CommandDelimiter);
			std::getline(tokenStream, parameters);

			return {commandName, parameters};
		}

		void InitFactoryMap(ArgumentsFacotryMap argumentsCreatorMap)
		{
			for (auto &factoryKv : argumentsCreatorMap)
			{
				std::string commandName = factoryKv.second->GetCommandName();
				std::for_each(commandName.begin(), commandName.end(), [](char &c)
							  { c = std::toupper(c); });

				mCommandArgumentsCreator.emplace(commandName, factoryKv.second);
			}
		}
	};
}