#pragma once

#ifndef CONSOLE_COMMANDS
#define CONSOLE_COMMANDS

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <API/encryptionApi.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

class ConsoleCommands
{
private:
  typedef std::function<void(const std::vector<std::string>&)> ConsoleFunction;
  std::unordered_map<std::string, ConsoleFunction> CLICommands;

  ConsoleCommands() { init(); }

  ConsoleCommands(const ConsoleCommands &) = delete;
  ConsoleCommands &operator=(const ConsoleCommands &) = delete;

  void init();
  void show_help(const std::vector<std::string> &args);

public:
  static ConsoleCommands &get_instance()
  {
    static ConsoleCommands instance;
    return instance;
  }

  static void run_command(
      const std::string &commandName,
      const std::vector<std::string> &args);
};

#endif