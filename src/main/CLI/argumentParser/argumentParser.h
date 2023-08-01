#pragma once

#ifndef ARGUMENT_PARSER
#define ARGUMENT_PARSER

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/global/exceptionHandling.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

class ArgumentParser
{
private:
  static constexpr char OPTION_MARKER = '-';

public:
  static std::unordered_map<std::string, std::string> parse_args(
      const std::vector<std::string> &args);
};

#endif