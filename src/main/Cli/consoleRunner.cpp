#include "consoleRunner.h"

void ConsoleRunner::run()
{
  if (argumentConsumer.get_command_name().empty())
  {
    FunctionLibrary::run_default_function();
    return;
  }

  FunctionLibrary::run_function(argumentConsumer);
}
