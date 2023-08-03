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
  static void show_help(const ArgumentConsumer &argumentConsumer);

public:
  static std::unordered_map<std::string, ConsoleFunction> get_mapped_functions();
  static void run_default_function();
};

#endif