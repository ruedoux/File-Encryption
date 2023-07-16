#pragma once
#ifndef LOGGER_GLOBAL
#define LOGGER_GLOBAL

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

#include <global/global.h>
#include <mutex>

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

// Error checks
#define LOGGER_RETURN_IF_NOT_MATCH(is, shouldBe, returnOnFail) \
  if (is != shouldBe)                                          \
  {                                                            \
    Logger::get_instance().log_error(                          \
        LOGGER_GET_LINE, "Failed to compare: ",                \
        "Expected: ", std::to_string(shouldBe),                \
        ", but got: ", std::to_string(is));                    \
    return returnOnFail;                                       \
  }

#define LOGGER_RETURN_IF_FILE_NOT_OPEN(file, filePath, returnOnFail) \
  if (!file.is_open())                                               \
  {                                                                  \
    Logger::get_instance().log_error(                                \
        LOGGER_GET_LINE,                                             \
        "File is not open: ", filePath);                             \
    return returnOnFail;                                             \
  }

#define LOGGER_RETURN_IF_FILE_NOT_EXIST(filepath, returnOnFail) \
  if (!std::filesystem::is_regular_file(filePath))              \
  {                                                             \
    Logger::get_instance().log_error(                           \
        LOGGER_GET_LINE,                                        \
        "File does not exist: ", filePath);                     \
    return returnOnFail;                                        \
  }

// -------------------------------------------------
// Declarations
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
  void log(const std::string &msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);
    log_stdout("", concatenatedMessage);
  }

  template <typename... Args>
  void log_info(const std::string &msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);
    log_stdout(INFO_MARKER, concatenatedMessage);
  }

  template <typename... Args>
  void log_error(const std::string &msg, Args... args)
  {
    std::string concatenatedMessage = msg;
    (concatenatedMessage += ... += args);

    std::lock_guard<std::mutex> lock(mutex);
    if (!supressError)
    {
      log_stderr(ERROR_MARKER, concatenatedMessage);
    }
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