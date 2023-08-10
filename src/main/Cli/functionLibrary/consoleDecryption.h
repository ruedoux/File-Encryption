#pragma once

#ifndef DECRYPTION_FUNCTION
#define DECRYPTION_FUNCTION

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/encryptionApi.h>

#include "consoleFunction/consoleFunction.h"
#include "userInput.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ConsoleDecryption : public ConsoleFunction
{
protected:
  virtual void bound_function(const ArgumentConsumer &argumentConsumer) const override
  {
    const std::filesystem::path inputFilePath =
        argumentConsumer.get_required_argument("-i");
    const std::filesystem::path outputFilePath =
        argumentConsumer.get_required_argument("-o");
    const std::filesystem::path passwordFilePath =
        argumentConsumer.get_optional_argument("-fp");

    if (!FileAccess::file_exist(inputFilePath))
    {
      throw UserViewException("Input file doesnt exist: " + inputFilePath.string());
    }

    std::vector<BYTE> key;
    if (passwordFilePath.string().empty())
    {
      key = UserInput::get_input_from_console_hidden_as_bytes("Type key: ");
    }
    else if (FileAccess::file_exist(passwordFilePath))
    {
      FileAccess::read_bytes_from_file(
          passwordFilePath, key, 0, FileAccess::get_file_size(passwordFilePath));
    }
    else
    {
      throw UserViewException("Password file doesnt exist: " + passwordFilePath.string());
    }

    EncryptionApi::decrypt_file(inputFilePath, outputFilePath, key);
    Logger::log_ok("Decryption successful");
  }

public:
  ConsoleDecryption(const std::string &commandName)
      : ConsoleFunction(commandName)
  {
    add_description("Decrypts a given file.");
    add_required_option("-i", "Input File path.");
    add_required_option("-o", "Output File path.");
    add_optional_option("-fp", "Path to file with password.");
  }
};

#endif