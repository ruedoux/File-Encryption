#pragma once

#ifndef ARGUMENT_CONSUMER
#define ARGUMENT_CONSUMER

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/global/exceptionHandling.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

class ArgumentConsumer
{
private:
  static constexpr char OPTION_MARKER = '-';
  std::string commandName;
  std::unordered_map<std::string, std::string> mappedArgs;

  static std::unordered_map<std::string, std::string> parse_args_options(
      const std::vector<std::string> &args);

public:
  ArgumentConsumer() {}

  bool parse_input(const int argc, char *argv[]);
  std::string get_command_name() const;
  std::string get_optional_argument(const std::string &arg) const;
  std::string get_required_argument(const std::string &arg) const;
};

#endif