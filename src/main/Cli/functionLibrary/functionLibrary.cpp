#include "functionLibrary.h"

std::unordered_map<std::string, std::unique_ptr<ConsoleFunction>>
FunctionLibrary::get_mapped_functions()
{
  std::vector<std::unique_ptr<ConsoleFunction>> functions;
  functions.push_back(std::make_unique<ConsoleDecryptionFunction>("decryptfile"));
  functions.push_back(std::make_unique<ConsoleEncryptionFunction>("encryptfile"));

  std::unordered_map<std::string, std::unique_ptr<ConsoleFunction>> mappedFunctions;
  for (std::unique_ptr<ConsoleFunction> &consoleFunction : functions)
  {
    mappedFunctions[consoleFunction.get()->get_command_name()] = std::move(consoleFunction);
  }

  return mappedFunctions;
}

void FunctionLibrary::show_help()
{
  Logger::log("List of possible commands and their options.");
  std::unordered_map<std::string, std::unique_ptr<ConsoleFunction>> functions =
      get_mapped_functions();
  for (auto &[commandName, consoleFunction] : functions)
  {
    Logger::log("----------------------------------------------------");
    Logger::log("\tCommand name: " + commandName);
    Logger::log("");
    Logger::log("\tDescription: ");
    Logger::log("\t\t" + consoleFunction.get()->get_description());

    if (!consoleFunction.get()->get_required_options().empty())
    {
      Logger::log("");
      Logger::log("\tRequired argument list: ");
    }

    for (auto &[optionName, optionDescription] : consoleFunction.get()->get_required_options())
    {
      Logger::log("\t\t" + optionName + " [argument], " + optionDescription);
    }

    if (!consoleFunction.get()->get_optional_options().empty())
    {
      Logger::log("");
      Logger::log("\tOptional argument list: ");
    }

    for (auto &[optionName, optionDescription] : consoleFunction.get()->get_optional_options())
    {
      Logger::log("\t\t" + optionName + " [argument], " + optionDescription);
    }
  }
  Logger::log("----------------------------------------------------");
}