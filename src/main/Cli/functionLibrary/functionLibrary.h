#pragma once

#ifndef CONSOLE_LIBRARY
#define CONSOLE_LIBRARY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/encryptionApi.h>

#include "consoleFunction/consoleFunction.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class FunctionLibrary
{
private:
  static std::unordered_map<std::string, ConsoleFunction> get_mapped_functions();

  static void show_help(const ConsoleFunction &consoleFunction);
  static void encrypt_file(const ConsoleFunction &consoleFunction);

public:
  static void run_default_function();
  static void run_function(const ArgumentConsumer &argumentConsumer);
};

#endif