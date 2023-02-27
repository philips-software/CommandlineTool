#pragma once
#include <string>
#include <memory>

namespace CommandlineTool
{

	/*
		A base class for all command parameters
	*/
	class CommandParameters
	{
	public:
		CommandParameters() {}
		virtual ~CommandParameters() {}
	};

	/*
		Arguments that are used to identify a command and its parameters.
	*/
	class CommandArguments
	{
	public:
		CommandArguments(const std::string &commandName, std::shared_ptr<CommandParameters> params)
			: mCommandName(commandName),
			  mParameters(params)
		{
		}

		CommandArguments(const CommandArguments &other) = default;
		CommandArguments(CommandArguments &&other) = default;

		CommandArguments &operator=(const CommandArguments &) = default;
		CommandArguments &operator=(CommandArguments &&) = default;

		virtual ~CommandArguments() {}

		std::string GetCommandName() const { return mCommandName; }
		std::shared_ptr<CommandParameters> GetParameters() const { return mParameters; }

	private:
		std::string mCommandName;
		std::shared_ptr<CommandParameters> mParameters;
	};
}