#pragma once
#ifndef LOGGER_GLOBAL
#define LOGGER_GLOBAL

// -------------------------------------------------
// DEPENDENCIES
// -------------------------------------------------

#include "global.h"

#include <cstdarg>

// -------------------------------------------------
// Macros
// -------------------------------------------------

#define LOGGER_GET_LINE "(" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + ") "

// Ansi colors
#define _BOLD "\033[1m"
#define _RED "\033[31m"
#define _GREEN "\033[32m"
#define _BLUE "\033[34m"
#define _ANSI_RESET "\033[0m"

// -------------------------------------------------
// DECLARATIONS
// -------------------------------------------------

namespace
{
  static const std::string INFO_MARKER =
      std::string(_BOLD) + std::string(_BLUE) + "[INFO] ";
  static const std::string ERROR_MARKER =
      std::string(_BOLD) + std::string(_RED) + "[ERROR] ";
}

class Logger
{
private:
  Logger() {}

public:
  template <typename... Args>
  static void log(const std::string &msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);
    log_stdout("", concatenatedMessage);
  }

  template <typename... Args>
  static void log_info(const std::string &msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);
    log_stdout(INFO_MARKER, concatenatedMessage);
  }

  template <typename... Args>
  static void log_error(const std::string &msg, Args... args)
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