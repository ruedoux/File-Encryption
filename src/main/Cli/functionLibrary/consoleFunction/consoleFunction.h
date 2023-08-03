#pragma once

#ifndef CONSOLE_FUNCTION
#define CONSOLE_FUNCTION

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "argumentConsumer/argumentConsumer.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ConsoleFunction
{
private:
  std::function<void(const ArgumentConsumer &)> bindedFunction;
  std::string description;
  std::vector<std::string> requiredOptions;

public:
  ConsoleFunction() {}
  ConsoleFunction(const std::function<void(const ArgumentConsumer &)> &functionToBind)
      : bindedFunction(functionToBind) {}

  void add_required_option(const std::string &option);
  void add_description(const std::string &desc);
  void run_bound_function(const ArgumentConsumer &argumentConsumer);
};

#endif