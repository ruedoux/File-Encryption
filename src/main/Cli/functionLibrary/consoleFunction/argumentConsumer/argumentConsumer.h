#pragma once

#ifndef ARGUMENT_CONSUMER
#define ARGUMENT_CONSUMER

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/global/exceptionHandling.h>

#include "argumentParser.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ArgumentConsumer
{
private:
  std::string commandName;
  std::unordered_map<std::string, std::string> mappedArgs;

public:
  ArgumentConsumer() {}

  bool parse_input(const int argc, char *argv[]);
  std::string get_command_name() const;
  std::string get_optional_argument(const std::string &arg) const;
  std::string get_required_argument(const std::string &arg) const;
};

#endif