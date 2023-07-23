#pragma once
#ifndef LOGGER_GLOBAL
#define LOGGER_GLOBAL

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

#include "global.h"

// -------------------------------------------------
// Macros
// -------------------------------------------------

#define LOGGER_GET_LINE "(" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + ") "
#define LOGGER_LOG_ERROR(...) Logger::get_instance()::log_error(LOGGER_GET_LINE + __VA_ARGS__)

#define ERROR_RETURN_IF_NOT_MATCH(is, shouldBe, returnOnFail) \
  if (is != shouldBe)                                         \
  {                                                           \
    Logger::get_instance().log_error(                         \
        LOGGER_GET_LINE + "Failed to compare!",               \
        "Expected: " + std::to_string(shouldBe),              \
        "But got: " + std::to_string(is));                    \
    return returnOnFail;                                      \
  }

#define ERROR_RETURN_IF_MORE(is, shouldBeLessOrEqual, returnOnFail)   \
  if (is > shouldBeLessOrEqual)                                       \
  {                                                                   \
    Logger::get_instance().log_error(                                 \
        LOGGER_GET_LINE + "Failed to compare!",                       \
        "Expected less than: " + std::to_string(shouldBeLessOrEqual), \
        "But got: " + std::to_string(is));                            \
    return returnOnFail;                                              \
  }

#define ERROR_RETURN_IF_LESS(is, shouldBeMoreOrEqual, returnOnFail)   \
  if (is < shouldBeMoreOrEqual)                                       \
  {                                                                   \
    Logger::get_instance().log_error(                                 \
        LOGGER_GET_LINE + "Failed to compare!",                       \
        "Expected less than: " + std::to_string(shouldBeMoreOrEqual), \
        "But got: " + std::to_string(is));                            \
    return returnOnFail;                                              \
  }

namespace
{
// Ansi colors
#define _BOLD "\033[1m"
#define _RED "\033[31m"
#define _GREEN "\033[32m"
#define _BLUE "\033[34m"
#define _ANSI_RESET "\033[0m"

#define VARARGS_FORMAT_STRING(stringName, varArgs) \
  std::stringstream ss;                            \
  ((ss << varArgs << '\n'), ...);                  \
  std::string stringName = ss.str()
}

// -------------------------------------------------
// Declarations
// -------------------------------------------------

namespace
{
  static const std::string INFO_MARKER = "[INFO] ";
  static const std::string ERROR_MARKER = "[ERROR] ";

  static const std::string INFO_MARKER_ANSI =
      std::string(_BOLD) + std::string(_BLUE) + INFO_MARKER;
  static const std::string ERROR_MARKER_ANSI =
      std::string(_BOLD) + std::string(_RED) + ERROR_MARKER;
}

class Logger
{
private:
  bool supressError;
  std::mutex mutex;

  Logger() { supressError = false; }

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

public:
  void set_error_supression(bool supress)
  {
    std::lock_guard<std::mutex> lock(mutex);
    supressError = supress;
  }

  static Logger &get_instance()
  {
    static Logger instance;
    return instance;
  }

  template <typename... Args>
  void log(Args... args)
  {
    VARARGS_FORMAT_STRING(msg, args);
    log_stdout(format_log(msg, ""));
  }

  template <typename... Args>
  void log_info(Args... args)
  {
    VARARGS_FORMAT_STRING(msg, args);
    log_stdout(format_log(INFO_MARKER_ANSI + msg, INFO_MARKER));
  }

  template <typename... Args>
  void log_error(Args... args)
  {
    VARARGS_FORMAT_STRING(msg, args);

    std::lock_guard<std::mutex> lock(mutex);
    if (!supressError)
    {
      log_stderr(format_log(ERROR_MARKER_ANSI + msg, ERROR_MARKER));
    }
  }

private:
  static void log_stdout(const std::string &concatenatedMessage);
  static void log_stderr(const std::string &concatenatedMessage);
  static std::string format_log(
      const std::string &src,
      const std::string &marker);
};

#endif