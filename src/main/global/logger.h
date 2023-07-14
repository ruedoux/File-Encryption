#pragma once
#ifndef LOGGER_GLOBAL
#define LOGGER_GLOBAL

// -------------------------------------------------
// DEPENDENCIES
// -------------------------------------------------

#include "global.h"

#include <cstdarg>

// -------------------------------------------------
// DECLARATIONS
// -------------------------------------------------

namespace
{
  static const std::string INFO_MARKER = "[INFO]";
  static const std::string ERROR_MARKER = "[ERROR]";
  static const std::string DEBUG_MARKER = "[DEBUG]";
}

class Logger
{
public:
  template<typename... Args>
  static void log_info(const std::string& msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);
    log_stdout(INFO_MARKER, concatenatedMessage);
  }

  template<typename... Args>
  static void log_error(const std::string& msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);
    log_stderr(ERROR_MARKER, concatenatedMessage);
  }

private:
  static void log_stdout(
      const std::string &marker,
      const std::string &concatenatedMessage);
  static void log_stderr(
      const std::string &marker,
      const std::string &concatenatedMessage);
};

#endif