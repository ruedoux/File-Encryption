#include "commandConsumer.h"

std::string CommandConsumer::get_command_name() const
{
  return commandName;
}

std::string CommandConsumer::get_optional_argument(const std::string &arg) const
{
  if(mappedArgs.count(arg) == 0)
  {
    return "";
  }

  return mappedArgs.at(arg);
}

std::string CommandConsumer::get_required_argument(const std::string &arg) const
{
  if(mappedArgs.count(arg) == 0)
  {
    THROW_EXCEPTION("Required argument is missing: " + arg);
  }

  return mappedArgs.at(arg);
}

bool CommandConsumer::parse_input(const int argc, char *argv[])
{
  if(argc < 2)
  {
    return false;
  }

  commandName = GLOBAL::str_to_lower(static_cast<std::string>(argv[1]));

  std::vector<std::string> args;
  for (int i = 2; i < argc; i++)
  {
    args.push_back(GLOBAL::str_to_lower(static_cast<std::string>(argv[i])));
  }

  mappedArgs = ArgumentParser::parse_args_options(args);
  return true;
}