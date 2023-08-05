#pragma once

#ifndef CONSOLE_COMMANDS
#define CONSOLE_COMMANDS

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "functionLibrary/functionLibrary.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ConsoleRunner
{
private:
  ArgumentConsumer argumentConsumer;
  void run_default_function();
  void run_function(const ArgumentConsumer &argumentConsumer);

public:
  ConsoleRunner(const int argc, char *argv[])
  {
    argumentConsumer.parse_input(argc, argv);
  }

  void run();
};

#endif