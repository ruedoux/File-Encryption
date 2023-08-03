#include "argumentConsumer.h"

std::string ArgumentConsumer::get_command_name() const
{
  return commandName;
}

std::string ArgumentConsumer::get_optional_argument(const std::string &arg) const
{
  if(mappedArgs.count(arg) == 0)
  {
    return "";
  }

  return mappedArgs.at(arg);
}

std::string ArgumentConsumer::get_required_argument(const std::string &arg) const
{
  if(mappedArgs.count(arg) == 0)
  {
    THROW_EXCEPTION("Required argument is missing: " + arg);
  }

  return mappedArgs.at(arg);
}

bool ArgumentConsumer::parse_input(const int argc, char *argv[])
{
  if(argc < 2)
  {
    return false;
  }

  commandName = Global::str_to_lower(static_cast<std::string>(argv[1]));

  std::vector<std::string> args;
  for (int i = 2; i < argc; i++)
  {
    args.push_back(Global::str_to_lower(static_cast<std::string>(argv[i])));
  }

  mappedArgs = ArgumentParser::parse_args_options(args);

  return true;
}