#include "consoleFunction.h"

void ConsoleFunction::add_required_option(const std::string &option)
{
  requiredOptions.push_back(option);
}

void ConsoleFunction::add_description(const std::string &desc)
{
  description = description;
}

void ConsoleFunction::run_bound_function(const ArgumentConsumer &argumentConsumer)
{
  if(!bindedFunction)
  {
    THROW_EXCEPTION("Tried to call not bound console function!");
  }

  bindedFunction(argumentConsumer);
}