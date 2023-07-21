#pragma once
#ifndef ERROR_HANDLING
#define ERROR_HANDLING

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

#include "logger.h"

// -------------------------------------------------
// Macros
// -------------------------------------------------

#define ERROR_RETURN_IF_NOT_MATCH(is, shouldBe, returnOnFail) \
  if (is != shouldBe)                                         \
  {                                                           \
    Logger::get_instance().log_error(                         \
        LOGGER_GET_LINE + "Failed to compare: ",              \
        "Expected: " + std::to_string(shouldBe),              \
        "But got: " + std::to_string(is));                    \
    return returnOnFail;                                      \
  }

#define ERROR_RETURN_IF_CONDITION_TRUE(condition, returnOnFail, ...) \
  if (condition)                                                     \
  {                                                                  \
    Logger::get_instance().log_error(                                \
        LOGGER_GET_LINE + __VA_ARGS__);                              \
    return returnOnFail;                                             \
  }

#define ERROR_RETURN_IF_FILE_NOT_OPEN(file, filePath, returnOnFail) \
  if (!file.is_open())                                              \
  {                                                                 \
    Logger::get_instance().log_error(                               \
        LOGGER_GET_LINE + "File is not open: ", filePath);          \
    return returnOnFail;                                            \
  }

#define ERROR_RETURN_IF_FILE_NOT_EXIST(filepath, returnOnFail) \
  if (!std::filesystem::is_regular_file(filePath))             \
  {                                                            \
    Logger::get_instance().log_error(                          \
        LOGGER_GET_LINE + "File does not exist: ", filePath);  \
    return returnOnFail;                                       \
  }

#define ERROR_RETURN_IF_FILE_OPERATION_FAILED(fileOperation, returnOnFail, ...) \
  if (!(fileOperation))                                                         \
  {                                                                             \
    Logger::get_instance().log_error(                                           \
        LOGGER_GET_LINE + __VA_ARGS__);                                         \
    return returnOnFail;                                                        \
  }

#endif