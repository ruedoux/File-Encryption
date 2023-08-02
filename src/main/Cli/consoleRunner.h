#pragma once

#ifndef CONSOLE_COMMANDS
#define CONSOLE_COMMANDS

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/encryptionApi.h>

#include "commandConsumer/commandConsumer.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ConsoleRunner
{
private:
  typedef std::function<void(void)> ConsoleFunction;
  std::unordered_map<std::string, ConsoleFunction> commandMap;
  CommandConsumer consoleCommandConsumer;

  void init();
  void show_help();
  void encrypt_file();

public:
  ConsoleRunner(const int argc, char *argv[])
  {
    init();
    consoleCommandConsumer.parse_input(argc, argv);
  }

  void run();
};

#endif