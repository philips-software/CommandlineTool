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