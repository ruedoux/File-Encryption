#include "consoleRunner.h"

void ConsoleRunner::init()
{
  CLICommands["help"] = std::bind(&ConsoleRunner::show_help, this);
}

void ConsoleRunner::run()
{
  static std::mutex commandMutex;
  std::lock_guard<std::mutex> lock(commandMutex);

  if (CLICommands.count(consoleCommandConsumer.get_command_name()) == 0)
  {
    CLICommands["help"]();
  }
  else
  {
    CLICommands[consoleCommandConsumer.get_command_name()]();
  }
}

void ConsoleRunner::show_help()
{
  Logger::log(
      "This is template help message.",
      "Nothing to see here!");
}

void ConsoleRunner::encrypt_file()
{
  
}