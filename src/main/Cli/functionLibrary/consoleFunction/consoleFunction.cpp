#include "consoleFunction.h"

std::string ConsoleFunction::get_description() const
{
  return _description;
}

std::string ConsoleFunction::get_command_name() const
{
  return _commandName;
}

std::unordered_map<std::string, std::string> ConsoleFunction::get_required_options() const
{
  return requiredOptions;
}

std::string ConsoleFunction::get_reqired_option(const std::string &optionName) const
{
  if(requiredOptions.count(optionName) == 0)
  {
    THROW_EXCEPTION("Tried to access non existing required option in: " + _commandName + "\nOption: " + optionName);
  }

  return requiredOptions.at(optionName);
}

void ConsoleFunction::add_required_option(
    const std::string &option, const std::string &description)
{
  requiredOptions[option] = description;
}

void ConsoleFunction::add_description(const std::string &description)
{
  _description = description;
}

void ConsoleFunction::run_bound_function()
{
  if (!bindedFunction)
  {
    THROW_EXCEPTION("Tried to call not bound console function!");
  }

  bindedFunction(*this);
}