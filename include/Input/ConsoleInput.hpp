#pragma once
#include <iostream>
#include <string>

#include "Input/CommandTextInput.hpp"

namespace CommandlineTool
{
	class ConsoleInput : public CommandTextInput
	{
	public:
		ConsoleInput(ArgumentsFacotryMap argumentsCreators) : CommandTextInput(argumentsCreators) {}
		ConsoleInput(const ConsoleInput &other) = default;
		ConsoleInput(ConsoleInput &&other) noexcept = default;

	protected:
		std::string RecieveInput() override
		{
			std::string userInput;

			std::getline(std::cin, userInput);

			return userInput;
		}
	};
}