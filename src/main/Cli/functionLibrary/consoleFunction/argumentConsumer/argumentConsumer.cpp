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
    return std::string();
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

  mappedArgs = parse_args_options(args);

  return true;
}

std::unordered_map<std::string, std::string> ArgumentConsumer::parse_args_options(
    const std::vector<std::string> &args)
{
  std::unordered_map<std::string, std::string> parsedArgs;
  std::vector<size_t> optionIndexes;
  for (size_t i = 0; i < args.size(); i++)
  {
    const std::string arg = args.at(i);
    if (arg.at(0) == OPTION_MARKER)
    {
      optionIndexes.push_back(i);
    }
  }

  for (const size_t index : optionIndexes)
  {
    if ((index + 1 >= args.size()) || (std::find(optionIndexes.begin(), optionIndexes.end(), index + 1) != optionIndexes.end()))
    {
      throw UserViewException("Option has no valid argument: " + args.at(index));
    }

    parsedArgs[args.at(index)] = args.at(index + 1);
  }

  return parsedArgs;
}