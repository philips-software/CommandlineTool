#pragma once
#include <vector>
#include <future>

#include "Executioner.hpp"
#include "Input/CommandArguments.hpp"

namespace CommandlineTool
{
	/*
		Executes the commands using std::async on a new thread. 
		The command must be thread safe.
	*/
	class AsyncExecutioner final : public Executioner
	{
	public:
		 AsyncExecutioner() = default;
		 virtual ~AsyncExecutioner() = default;

		 void Execute(const CommandArguments& arguments) override
		 {
			 auto syncF = [=]()
			 {
				 this->Executioner::Execute(arguments);
			 };

			 auto future = std::async(std::launch::async, syncF);
			 mTasks.push_back(std::move(future));
		 }

	private:
		std::vector<std::future<void>> mTasks;
	};

}