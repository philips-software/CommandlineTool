#pragma once

#include <string>
#include <iostream>
#include "Input/Command.hpp"
#include "Input/CommandArguments.hpp"
#include "Parsers/CommandArgumentsCreator.hpp"

class SayHelloCommand : public CommandlineTool::Command
{
public:
	/*
		A Command must have a execution logic.
	*/
	virtual void Execute(const CommandlineTool::CommandArguments& args)
	{
		std::cout << "Hello World\n";
	}

	/*
		A command is identified by a given name.
		An execution engine may use it to identify different commands.
	*/
	virtual std::string GetName()
	{
		using namespace std::string_literals;

		return "say_hello"s;
	}
	constexpr static auto& Name = "say_hello";
};

class SayHelloArgumentsCreator : public CommandlineTool::CommandArgumentsCreator
{
public:
	/*
		Outputs a CommandArguments for key-value arguments.
	*/
	virtual CommandlineTool::CommandArguments CreateArguments(std::map<std::string, std::string> arguments) override
	{
		return { "say_hello", {} };
	}

	/*
			  Gets a help text for the argument creator - what argument it expects and what are the values.
			  Help text is in the arguments creator because it only knows what text it parses and what encoding/format it is.
		  */
	virtual std::string GetHelpText() override
	{
		return "Says hello";
	}

	/*
			  Gets the name of the command it parses arguments for.
		  */
	virtual std::string GetCommandName() override
	{
		return "say_hello";
	}
};