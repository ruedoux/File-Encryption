#include "functionLibrary.h"

void FunctionLibrary::run_default_function()
{
  show_help(ConsoleFunction());
}

void FunctionLibrary::run_function(const ArgumentConsumer &argumentConsumer)
{
  auto mappedFunctions = get_mapped_functions();
  const std::string commandName = argumentConsumer.get_command_name();

  if (mappedFunctions.count(commandName) == 0)
  {
    throw UserViewException("No command with name: " + commandName);
  }

  ConsoleFunction consoleFunction = mappedFunctions[commandName];

  for (auto &[option, description] : consoleFunction.get_required_options())
  {
    if (argumentConsumer.get_required_argument(option).empty())
    {
      throw UserViewException("Required argument is missing! \nOption: " + option + "\nDescription: " + description);
    }
  }

  consoleFunction.run_bound_function();
}

std::unordered_map<std::string, ConsoleFunction> FunctionLibrary::get_mapped_functions()
{
  ConsoleFunction helpFunction(
      &FunctionLibrary::show_help,
      "help");
  helpFunction.add_description("Shows list of all possible commands for the application.");
  
  ConsoleFunction encryptionFunction(
      &FunctionLibrary::encrypt_file,
      "encryptfile");
  encryptionFunction.add_description("Encrypts a given file.");
  encryptionFunction.add_required_option("-i", "Input File path.");
  encryptionFunction.add_required_option("-o", "Output File path.");

  std::vector<ConsoleFunction> functions({helpFunction, encryptionFunction});

  std::unordered_map<std::string, ConsoleFunction> mappedFunctions;
  for (ConsoleFunction &consoleFunction : functions)
  {
    mappedFunctions[consoleFunction.get_command_name()] = consoleFunction;
  }

  return mappedFunctions;
}

void FunctionLibrary::show_help(const ConsoleFunction &consoleFunction)
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

void FunctionLibrary::encrypt_file(const ConsoleFunction &consoleFunction)
{
  const std::string inputFilePath = consoleFunction.get_reqired_option("-i");
  const std::string outputFilePath = consoleFunction.get_reqired_option("-o");
}