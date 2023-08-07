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

std::unordered_map<std::string, std::string> ConsoleFunction::get_optional_options() const
{
  return optionalOptions;
}

std::string ConsoleFunction::get_required_option(const std::string &optionName) const
{
  if (requiredOptions.count(optionName) == 0)
  {
    THROW_EXCEPTION("Tried to access non existing required option in: " + _commandName + "\nOption: " + optionName);
  }

  return requiredOptions.at(optionName);
}

std::string ConsoleFunction::get_optional_option(const std::string &optionName) const
{
  if (requiredOptions.count(optionName) == 0)
  {
    return "";
  }

  return optionalOptions.at(optionName);
}

void ConsoleFunction::add_required_option(
    const std::string &option, const std::string &description)
{
  requiredOptions[option] = description;
}

void ConsoleFunction::add_optional_option(
    const std::string &option, const std::string &description)
{
  optionalOptions[option] = description;
}

void ConsoleFunction::add_description(const std::string &description)
{
  _description = description;
}

void ConsoleFunction::run_bound_function(const ArgumentConsumer &argumentConsumer)
{
  for (auto &[option, description] : this->get_required_options())
  {
    if (argumentConsumer.get_required_argument(option).empty())
    {
      throw UserViewException("Required argument is missing! \nOption: " + option + "\nDescription: " + description);
    }
  }

  if (!bindedFunction)
  {
    THROW_EXCEPTION("Tried to call not bound console function!");
  }

  bindedFunction(argumentConsumer);
}