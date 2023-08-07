#include "consoleRunner.h"

void ConsoleRunner::run()
{
  if (argumentConsumer.get_command_name().empty())
  {
    run_default_function();
    return;
  }

  run_function(argumentConsumer);
}

void ConsoleRunner::run_default_function()
{
  FunctionLibrary::show_help();
}

void ConsoleRunner::run_function(const ArgumentConsumer &argumentConsumer)
{
  auto mappedFunctions = FunctionLibrary::get_mapped_functions();
  const std::string commandName = argumentConsumer.get_command_name();

  if(commandName == "help")
  {
    run_default_function();
    return;
  }

  if (mappedFunctions.count(commandName) == 0)
  {
    throw UserViewException("No command with name: " + commandName);
  }

  mappedFunctions[commandName].get()->run_bound_function(argumentConsumer);
}