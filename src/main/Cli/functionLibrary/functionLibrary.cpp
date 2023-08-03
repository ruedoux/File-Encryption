#include "functionLibrary.h"

void FunctionLibrary::run_default_function()
{
  show_help(ArgumentConsumer());
}

std::unordered_map<std::string, ConsoleFunction> FunctionLibrary::get_mapped_functions()
{
  std::unordered_map<std::string, ConsoleFunction> mappedFunctions;

  ConsoleFunction helpFunction(
    std::bind(&FunctionLibrary::show_help, std::placeholders::_1));
  mappedFunctions["help"] = helpFunction;

  return mappedFunctions;
}

void FunctionLibrary::show_help(const ArgumentConsumer &argumentConsumer)
{
  Logger::log(
      "This is template help message.",
      "Nothing to see here!");
}