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
protected:
  std::string _commandName;
  std::string _description;
  std::unordered_map<std::string, std::string> requiredOptions;
  std::unordered_map<std::string, std::string> optionalOptions;

  ConsoleFunction(std::string commandName)
      : _commandName(commandName) {}

  void add_required_option(const std::string &option, const std::string &description);
  void add_optional_option(const std::string &option, const std::string &description);
  void add_description(const std::string &description);
  virtual void bound_function(const ArgumentConsumer &argumentConsumer) const = 0;

public:
  std::string get_description() const;
  std::string get_command_name() const;
  std::string get_required_option(const std::string &optionName) const;
  std::string get_optional_option(const std::string &optionName) const;
  std::unordered_map<std::string, std::string> get_required_options() const;
  std::unordered_map<std::string, std::string> get_optional_options() const;
  void run_bound_function(const ArgumentConsumer &argumentConsumer) const;
};

#endif