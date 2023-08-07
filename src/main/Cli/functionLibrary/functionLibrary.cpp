#include "functionLibrary.h"

const std::string FunctionLibrary::DEFAULT_FUNCTION_NAME = "help";

std::unordered_map<std::string, ConsoleFunction> FunctionLibrary::get_mapped_functions()
{
  ConsoleFunction helpFunction(
      &FunctionLibrary::show_help,
      DEFAULT_FUNCTION_NAME);
  helpFunction.add_description("Shows list of all possible commands for the application.");

  ConsoleFunction encryptionFunction(
      &FunctionLibrary::encrypt_file,
      "encryptfile");
  encryptionFunction.add_description("Encrypts a given file.");
  encryptionFunction.add_required_option("-i", "Input File path.");
  encryptionFunction.add_required_option("-o", "Output File path.");
  encryptionFunction.add_optional_option("-fp", "Path to file with password.");

  ConsoleFunction decryptionFunction(
      &FunctionLibrary::decrypt_file,
      "decryptfile");
  decryptionFunction.add_description("Decrypts a given file.");
  decryptionFunction.add_required_option("-i", "Input File path.");
  decryptionFunction.add_required_option("-o", "Output File path.");
  encryptionFunction.add_optional_option("-fp", "Path to file with password.");

  std::vector<ConsoleFunction> functions(
      {helpFunction, encryptionFunction, decryptionFunction});

  std::unordered_map<std::string, ConsoleFunction> mappedFunctions;
  for (ConsoleFunction &consoleFunction : functions)
  {
    mappedFunctions[consoleFunction.get_command_name()] = consoleFunction;
  }

  return mappedFunctions;
}

void FunctionLibrary::show_help(const ArgumentConsumer &argumentConsumer)
{
  Logger::log("List of possible commands and their options.");
  std::unordered_map<std::string, ConsoleFunction> functions = get_mapped_functions();
  for (auto &[commandName, consoleFunction] : functions)
  {
    Logger::log("----------------------------------------------------");
    Logger::log("\tCommand name: " + commandName);
    Logger::log("");
    Logger::log("\tDescription: ");
    Logger::log("\t\t" + consoleFunction.get_description());

    if (!consoleFunction.get_required_options().empty())
    {
      Logger::log("");
      Logger::log("\tRequired argument list: ");
    }

    for (auto &[optionName, optionDescription] : consoleFunction.get_required_options())
    {
      Logger::log("\t\t" + optionName + " [argument], " + optionDescription);
    }
  }
  Logger::log("----------------------------------------------------");
}

void FunctionLibrary::encrypt_file(const ArgumentConsumer &argumentConsumer)
{
  const std::filesystem::path inputFilePath =
      argumentConsumer.get_required_argument("-i");
  const std::filesystem::path outputFilePath =
      argumentConsumer.get_required_argument("-o");
  

  if (!FileAccess::file_exist(inputFilePath))
  {
    throw UserViewException("Input file doesnt exist: " + inputFilePath.string());
  }

  const std::vector<BYTE> key =
      UserInput::get_input_from_console_hidden_as_bytes("Type key: ");

  EncryptionApi::encrypt_file(inputFilePath, outputFilePath, key);
  Logger::log_info("Encryption successful");
}

void FunctionLibrary::decrypt_file(const ArgumentConsumer &argumentConsumer)
{
  const std::filesystem::path inputFilePath =
      argumentConsumer.get_required_argument("-i");
  const std::filesystem::path outputFilePath =
      argumentConsumer.get_required_argument("-o");

  if (!FileAccess::file_exist(inputFilePath))
  {
    throw UserViewException("Input file doesnt exist: " + inputFilePath.string());
  }

  const std::vector<BYTE> key =
      UserInput::get_input_from_console_hidden_as_bytes("Type key: ");

  EncryptionApi::decrypt_file(inputFilePath, outputFilePath, key);
  Logger::log_info("Decryption successful");
}
