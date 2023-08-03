#include "consoleRunner.h"

void ConsoleRunner::run()
{
  if (argumentConsumer.get_command_name().empty())
  {
    FunctionLibrary::run_default_function();
    return;
  }

  auto commandMap = FunctionLibrary::get_mapped_functions();

  if (commandMap.count(argumentConsumer.get_command_name()) == 0)
  {
    THROW_EXCEPTION("No command with name: " + argumentConsumer.get_command_name());
  }
  else
  {
    commandMap[argumentConsumer.get_command_name()]
        .run_bound_function(argumentConsumer);
  }
}
