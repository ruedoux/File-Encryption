#include "consoleCommands.h"

void ConsoleCommands::init()
{
  CLICommands["help"] =
      std::bind(&ConsoleCommands::show_help, this, std::placeholders::_1);
}

void ConsoleCommands::run_command(
    const std::string &commandName,
    const std::vector<std::string> &args)
{
  static std::mutex commandMutex;
  std::lock_guard<std::mutex> lock(commandMutex);
  if (get_instance().CLICommands.count(commandName) == 0)
  {
    get_instance().CLICommands["help"](args);
  }
  else
  {
    get_instance().CLICommands[commandName](args);
  }
}

void ConsoleCommands::show_help(const std::vector<std::string> &args)
{
  Logger::log(
      "This is template help message.",
      "Nothing to see here!");
}

void ConsoleCommands::encrypt_file(const std::vector<std::string> &args)
{
}