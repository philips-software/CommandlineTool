#pragma once

#include <any>
#include <map>
#include <string>
#include "../libs/cxxopts/cxxopts.hpp"

namespace CommandlineTool
{
	/*
		Helps to parse more easily the arguments of the executable using cxxopts library.
		In the form of:
		-s
		--longOption=Value
		--longOption value
	*/
	class ExecutableArgumentsParser
	{
	public:
		ExecutableArgumentsParser(std::string toolName, std::string description = "")
		{
			mOptions = std::make_unique<cxxopts::Options>(toolName, description);
		}

		/*
			Adds a single option to parse
			optionRule - short options,Long option, ie: "h,help"
			description - A description on the option.
			value - What kind of value, defined by cxxopts::value. Default is bool.
			arg_help - Help group for argument
		*/
		ExecutableArgumentsParser* AddOption(std::string optionRule, std::string description,
			std::shared_ptr<const cxxopts::Value> value = ::cxxopts::value<bool>(),
			std::string argumentHelp = "", std::string groupName = "")
		{
			mOptions->add_option(groupName, { optionRule, description, value, argumentHelp });
			return this;
		}


		/*
			Parses the given options and outputs the result.
		*/
		cxxopts::ParseResult Parse(int argc, char** argv, bool& outShouldContinue)
		{
			auto result = mOptions->parse(argc, argv);

			if (result.count("help") > 0)
			{
				auto helpText = mOptions->help();
				std::cout << helpText << std::endl;
				outShouldContinue = false;
				return result;
			}

			outShouldContinue = true;
			return result;
		}

	private:
		std::unique_ptr<cxxopts::Options> mOptions;
	};
}

