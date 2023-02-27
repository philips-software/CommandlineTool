#pragma once
#include <map>
#include <string>
#include <sstream>
#include "../Utils/StringHelper.hpp"

namespace CommandlineTool
{
	/*
		Parsing textual input of commands to a key-value map.
	*/
	class CommandParametersParser
	{
	public:
		/*
			Parses arguments for commands:
			Example: [param]=[value] [param2]=[value2]
		*/
		virtual std::map<std::string, std::string> Parse(std::string text)
		{
			// Arguments are constructed from spaces and each parameter is seperated by eqauls.

			constexpr auto argumentsDelimiter = ' ';
			constexpr auto parameterDelimiter = '=';

			std::istringstream inputStream(text);

			std::map<std::string, std::string> allArguments;
			std::string singleArgument;
			while (std::getline(inputStream, singleArgument, argumentsDelimiter))
			{
				if (singleArgument.find(parameterDelimiter) == std::string::npos)
				{
					// Allow CMDTL to recieve parameters without value.
					allArguments[singleArgument] = "";
					continue;
				}
				auto keyValue = StringHelper::Split(singleArgument, parameterDelimiter);
				auto& argumentName = keyValue.first;
				allArguments[argumentName] = keyValue.second;
			}

			return allArguments;
		}
	};
}