#include "argumentParser.h"

std::unordered_map<std::string, std::string> ArgumentParser::parse_args_options(
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
