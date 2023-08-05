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
  FunctionLibrary::get_mapped_functions()[FunctionLibrary::DEFAULT_FUNCTION_NAME]
      .run_bound_function(argumentConsumer);
}

void ConsoleRunner::run_function(const ArgumentConsumer &argumentConsumer)
{
  auto mappedFunctions = FunctionLibrary::get_mapped_functions();
  const std::string commandName = argumentConsumer.get_command_name();

  if (mappedFunctions.count(commandName) == 0)
  {
    throw UserViewException("No command with name: " + commandName);
  }

  ConsoleFunction consoleFunction = mappedFunctions[commandName];
  consoleFunction.run_bound_function(argumentConsumer);
}