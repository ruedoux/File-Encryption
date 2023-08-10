#pragma once

#ifndef CONSOLE_LIBRARY
#define CONSOLE_LIBRARY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/encryptionApi.h>

#include "consoleDecryption.h"
#include "consoleEncryption.h"
#include "consoleDecryptPrint.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class FunctionLibrary
{
public:
  static void show_help();
  static std::unordered_map<std::string, std::unique_ptr<ConsoleFunction>>
  get_mapped_functions();
};

#endif