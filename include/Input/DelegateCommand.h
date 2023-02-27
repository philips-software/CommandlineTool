#pragma once
#include <map>
#include <string>
#include <functional>

#include "Command.hpp"
#include "../Parsers/DelegateArgumentsCreator.hpp"

namespace CommandlineTool
{
	class DelegateCommand : public Command
	{
	protected:
		std::string mName;
		std::function<void(MapCommandParameters &)> mExecutor;

	public:
		DelegateCommand(std::string name, std::function<void(MapCommandParameters &)> exec) : mName(name), mExecutor(exec) {}
		virtual ~DelegateCommand() = default;

		// Inherited via Command
		void Execute(const CommandlineTool::CommandArguments &args) override
		{
			auto parms = GetParameters<MapCommandParameters>(args);
			mExecutor(*parms.get());
		}

		std::string GetName() override
		{
			return mName;
		}
	};

}