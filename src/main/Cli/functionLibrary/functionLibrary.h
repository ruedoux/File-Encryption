#pragma once

#ifndef CONSOLE_LIBRARY
#define CONSOLE_LIBRARY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/encryptionApi.h>

#include "consoleFunction/consoleFunction.h"
#include "userInput.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class FunctionLibrary
{
private:
  static void show_help(const ArgumentConsumer &argumentConsumer);
  static void encrypt_file(const ArgumentConsumer &argumentConsumer);
  static void decrypt_file(const ArgumentConsumer &argumentConsumer);

public:
  static const std::string DEFAULT_FUNCTION_NAME;

  static std::unordered_map<std::string, ConsoleFunction> get_mapped_functions();
};

#endif