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
  std::unordered_map<std::string, ConsoleFunction> CLICommands;
  CommandConsumer consoleCommandConsumer;

  void init();
  void show_help();
  void encrypt_file();

public:

  ConsoleRunner(const int argc, char *argv[]) 
  { 
    consoleCommandConsumer.parse_input(argc, argv);
    init(); 
  }
  
  void run();

};

#endif