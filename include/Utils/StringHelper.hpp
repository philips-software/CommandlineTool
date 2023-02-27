#pragma once

#include <string>
#include <algorithm>
#include <sstream>

namespace CommandlineTool
{
	class  StringHelper
	{
	public:
		static inline void ToUpperCase(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		}

		static inline std::pair<std::string, std::string> Split(std::string input, char delimiter)
		{
			std::istringstream tokenStream(input);
			std::pair<std::string, std::string> argumentKeyValue;
			std::string temp;

			// For performance I don't use a loop.
			if (std::getline(tokenStream, temp, delimiter))
			{
				argumentKeyValue.first = temp;
			}
			else
			{
				return {};
			}

			if (std::getline(tokenStream, temp, delimiter))
			{
				argumentKeyValue.second = temp;
			}
			else
			{
				return {};
			}
			return argumentKeyValue;
		}
	};
}