#include "consoleRunner.h"

void ConsoleRunner::init()
{
  commandMap["help"] = std::bind(&ConsoleRunner::show_help, this);
}

void ConsoleRunner::run()
{
  static std::mutex commandMutex;
  std::lock_guard<std::mutex> lock(commandMutex);

  if(consoleCommandConsumer.get_command_name().empty())
  {
    commandMap["help"]();
    return;
  }

  if (commandMap.count(consoleCommandConsumer.get_command_name()) == 0)
  {
    THROW_EXCEPTION("No command with name: " + consoleCommandConsumer.get_command_name());
  }
  else
  {
    commandMap[consoleCommandConsumer.get_command_name()]();
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
  std::string inFilePath = consoleCommandConsumer.get_required_argument("-i");
  std::string outFilePath = consoleCommandConsumer.get_required_argument("-o");
}