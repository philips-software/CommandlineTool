#pragma once

#include <string>
#include <memory>

#include "CommandArguments.hpp"

namespace CommandlineTool
{
	/*
		A simple logic execution unit for all types of commands.
	*/
	class Command
	{
	public:
		Command() = default;
		Command(Command &other) = default;
		Command(Command &&other) = default;
		virtual ~Command() = default;

		// TODO: Operator = & and &&.

		/*
			A Command must have a execution logic.
		*/
		virtual void Execute(const CommandArguments &args) = 0;

		/*
			A command is identified by a given name.
			An execution engine may use it to identify different commands.
		*/
		virtual std::string GetName() = 0;

	protected:
		/*
			The Parameters inside the CommandArguments is dynamic, therefore we need to cast it
			to the desired parameters in the derived command.
		*/
		template <class Params>
		std::shared_ptr<Params> GetParameters(const CommandArguments &args)
		{
			// Implementation in header to avoid compilation issues.
			auto baseParams = args.GetParameters();
			return std::dynamic_pointer_cast<Params>(baseParams);
		}
	};
}