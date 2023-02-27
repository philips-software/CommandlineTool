#pragma once
#include <string>
#include "CommandArgumentsCreator.hpp"

namespace CommandlineTool
{
    class MapCommandParameters : public CommandParameters
    {
    public:
        virtual ~MapCommandParameters() = default;

        std::map<std::string, std::string> Arguments;
    };

    class DelegateArgumentCreator : public CommandArgumentsCreator
    {
    protected:
        std::string mCommandName;

    public:
        DelegateArgumentCreator(std::string commandName) : mCommandName(commandName) {}
        virtual ~DelegateArgumentCreator() {}

        // Inherited via CommandArgumentsCreator
        virtual CommandArguments CreateArguments(std::map<std::string, std::string> arguments) override
        {
            auto args = std::make_shared<MapCommandParameters>();
            args->Arguments = arguments;

            return {mCommandName, args};
        }
        /*
		Gets a help text for the argument creator - what argument it expects and what are the values.
		Help text is in the arguments creator because it only knows what text it parses and what encoding/format it is.
	*/
        std::string GetHelpText() override { return mCommandName; }

        /*
			Gets the name of the command it parses arguments for.
		*/
        std::string GetCommandName() override
        {
            return mCommandName;
        }
    };
}
