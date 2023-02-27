# Commandline Tools
``CMDTL`` (``Commandline Tools``) is the easiest API to construct asynchronous interactive commandline tools.  

It features:
- [x] Interactive UX.  
- [x] Header only.  
- [x] Easy to use API.  
- [x] Lego-like component construction.  
- [x] Asynchronous and Synchronous command calls.  
- [x] Delegate or Dedicated commands.  
- [x] Command help manuals.  
- [x] Modular parser for command arguments.  
- [x] One time command execution (Call & Exit).  

``CMDTL`` was designed with ``OOP`` and ``SOLID`` in mind.  
It is extensible and modular and allows quick additions or alternation to the commanline behavior.  

## Why CMDTL?
The library packs all relevant behavior needed to craft an interactive commandline tool.  
It is designated for command based behavior, can be extended (In the future) to allow different inputs for commands like an HTTP input through GET commands.  

## Creating a command based tool in a CMD
Creating and configuring a default program was never this easy!  
We make a program - ``ConfigureDefault`` configure all the default strategies and then we ``Run`` it.  
``cxxopts`` is used to parse executable arguments.  

```cpp
#include <memory>
#include <string>
#include <Program.hpp>

int main(int argc, char **argv)
{
    using namespace CommandlineTool;
    std::string AppName{"ExampleOne"};
    auto program = std::make_shared<Program>(AppName);

    return program->ConfigureDefault({})->Run(argc, argv);
}
```

## Commands
A command may be a ``DelegateCommand`` or a dervied instance of ``CommandlineTool::Command``.  
A command needs "input", by default the ``Program`` uses a ``ConsoleInput``.  
The ``ConsoleInput`` needs to translate strings typed by a user into C++ classes/structs.  

The ``Input`` is translated into a dictionary of parameter name and its value and translated by a ``CommandArgumentsCreator``.  

The ``CommandArgumentsCreator`` outputs a ``CommandArguments`` which contains the command ``Name`` and it's ``CommandParameters``.  
To create your own parameter class you should inherit ``CommandParameters``.  

A basic command example is [SayHelloCommand](/examples/Example_2_BasicCommand/SayHelloCommand.hpp).  

## Overview

### What is our code of conduct?  
[CodeOfConduct](./Code%20Of%20Conduct.md)

### How to contribute?  
[Contributing](./Contributing.md)


### Who are the Maintainers?  
[Maintainers](./MAINTAINERS.md)

### What has changed?  
[ChangeLog](./Change%20Log.md)

### What License are we using?  
[LICENSE](./license)

## Development
See [Contributing](./Contributing.md) for how to make contributions.  
We work by open source standards -  
If you have a bug, issue, feature and you want to resolve it yourself ``fork`` the repository and create a ``Pull request`` once you are done!  
We welcome all contributors :)   