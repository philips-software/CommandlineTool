#pragma once
#include <iostream>
#include <string>
#include "CommandTextInput.hpp"

namespace CommandlineTool
{
	/*
		One time input encapsulates a single command input as text to parse and run.
		Used in a non interactive scenario.
	*/
	class OneTimeInput : public CommandTextInput
	{
	public:
		OneTimeInput(std::string oneTimeInput, ArgumentsFacotryMap map) : CommandTextInput(map), mOneTimeInput(oneTimeInput) {}

		OneTimeInput(ArgumentsFacotryMap argumentsCreators) : CommandTextInput(argumentsCreators) {}
		OneTimeInput(const CommandTextInput &other) : CommandTextInput(other) {}
		OneTimeInput(const OneTimeInput &other) = default;
		OneTimeInput(OneTimeInput &&other) noexcept = default;

		void SetCommand(std::string oneTimeCommand)
		{
			mOneTimeInput = oneTimeCommand;
		}

	protected:
		std::string RecieveInput() override
		{
			return mOneTimeInput;
		}

		std::string mOneTimeInput;
	};
}