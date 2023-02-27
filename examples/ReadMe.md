# Commandline Tool - CMDTL
``Commandline tool`` is a library that enhances commandline capabilities through standard arguments and commands.  
It enables sync and async commands out of the box.  
For advanced usage it provides the "Engine" parts to construct any commandline tool through input, parsing and execution customization.  
E.g:
- Input from network devices
- Parsing json/xml formats
- Remote machine executions

# Key concepts

## Program
Any "Program" is a "Tool" that is designed to perform certain tasks.  
Each task is a command.  
A program may work synchronously or asynchronously.  

## Arguments/Parameters
There are 2 types of parameters:  
- Executable parameters given by a user - ``Tool.exe Param1 Param2 --option``.  
- Command parameters - Key/Value paris given to a single command: ``Say message=Hello``.  

## Command input
Input of commands is decoupled from the execution.  
The default input is console input - however it may work with a remote websocket or even a file.  

## Command Execution
The execution engine executes given commands once they are parsed correctly.  
Each parsing is dnoe by an ``ArgumentCreator`` to transform string data into ``C++ structs``.  

## Handlers
Handlers may execute code in the beginning of the program and in the end.  
For example it's very common to spawn addition executables and close them in the end.  
Or if files were opened, safely close them in the end.  

# Examples
The examples folder will provide some capabilities of the framework.  

[Async executioner](./examples/Exaple_3_AsyncExecutioner/)


## Example 1: Basic sync tool
[Basic syncrhonous tool](./examples/Example_1_BasicSyncTool/)

How to include and build a simple ``Program``.  

The program has no commands.  

To run a simple program configured to default parsers and a synchronous executior use the ``ConfigureDefault`` method of the ``Program`` class.  
By default ``help`` and ``exit`` commands are configured.  

```c++
using namespace CommandlineTool;
std::string AppName{"ExampleOne"};
auto program = std::make_shared<Program>(AppName);

return program->ConfigureDefault({})->Run(argc, argv);
```

## Example 2: Basic Command
[Basic Command](./examples/Example_2_BasicCommand/)

A basic ``HelloCommand`` is added, this requires 3 classes:  
- ``HelloParameters`` which implements ``CommandlineTool::CommandParameters``.  
- ``SayHelloArgumentsCreator`` which implements ``CommandlineTool::CommandArgumentsCreator``.  
- ``SayHelloCommand`` which implements ``CommandlineTool::Command``.  

``Arguments`` are key-value pairs constructed from strings.  
The ``Arguments`` are received from the parser (Most cases it's the console).  
These are needed to be translated into ``Parameters`` so the command can receive them.  
And lastly the Command has details about its execution, help text and its name.  

## Exaple_3_AsyncExecutioner
[Async Executioner](./examples/Exaple_3_AsyncExecutioner/)

The third example demonstrates 2 things:  

### Async Executioner
By simply specifying:  
```c++
		->ConfigureCommandExecutioner(std::make_shared<AsyncExecutioner>())
```

We replace the default executioner with the ``AsyncExecutioner``.  

### Delegate Commands
By using the ``DelegateCommand`` and ``DelegateArgumentCreator`` we can create delegate commands.  
This is very helpful for simple tools that don't want to create too many files.  
You can specify this all in the ``main.cpp`` file.  

``SayByeCommand``:  
```c++
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
```

This is important to note that naming of the commands are important.  
Delegate command help texts are not available yet.  

