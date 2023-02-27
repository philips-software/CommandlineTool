#include <memory>
#include <string>
#include <iostream>
#include "Program.hpp"
#include "Input/DelegateCommand.h"
#include "Parsers/DelegateArgumentsCreator.hpp"
#include "SayHelloCommand.hpp"
#include "AsyncExecutioner.hpp"

int main(int argc, char **argv)
{
	using namespace CommandlineTool;
	std::string AppName{"ExampleOne"};

	auto sayByeCommand = std::make_shared<DelegateCommand>("say_bye",

														   [](MapCommandParameters &params)
														   {
															   if (params.Arguments.size() > 0)
															   {
																   std::cout << "Bye " << params.Arguments[0] << "\n";
															   }
															   else
															   {
																   std::cout << "Bye\n";
															   }
														   });

	return std::make_shared<Program>(AppName)
		->ConfigureDefault({{SayHelloCommand::Name, std::make_shared<SayHelloArgumentsCreator>()},
							{"say_bye", std::make_shared<DelegateArgumentCreator>(("say_bye"))}})
		->ConfigureCommandExecutioner(std::make_shared<AsyncExecutioner>())
		->ConfigureCommand(std::make_shared<SayHelloCommand>())
		->ConfigureCommand(sayByeCommand)
		->Run(argc, argv);
}