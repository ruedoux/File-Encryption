// -------------------------------------------------
// Header included in all files (global includes and typedefs)
// -------------------------------------------------

#pragma once
#ifndef EXCEPTION_GLOBAL
#define EXCEPTION_GLOBAL

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

#include <stdexcept>

#include "logger.h"

// -------------------------------------------------
// Macros
// -------------------------------------------------

#define THROW_EXCEPTION(message) throw BaseException(message, LOGGER_GET_LINE)

#define THROW_EXCEPTION_IF_TRUE(shouldNotBeTrue) \
  if (shouldNotBeTrue)                           \
  {                                              \
    THROW_EXCEPTION(Logger::varargs_to_string(   \
        "Flag is true!"));                       \
  }

#define THROW_EXCEPTION_IF_NOT_MATCH(is, shouldBe) \
  if (is != shouldBe)                              \
  {                                                \
    THROW_EXCEPTION(Logger::varargs_to_string(     \
        "Failed to compare!",                      \
        "Expected: " + std::to_string(shouldBe),   \
        "But got: " + std::to_string(is)));        \
  }

#define THROW_EXCEPTION_IF_MORE(is, shouldBeLessOrEqual)              \
  if (is > shouldBeLessOrEqual)                                       \
  {                                                                   \
    THROW_EXCEPTION(Logger::varargs_to_string(                        \
        LOGGER_GET_LINE + "Failed to compare!",                       \
        "Expected less than: " + std::to_string(shouldBeLessOrEqual), \
        "But got: " + std::to_string(is)));                           \
  }

#define THROW_EXCEPTION_IF_LESS(is, shouldBeMoreOrEqual)              \
  if (is < shouldBeMoreOrEqual)                                       \
  {                                                                   \
    THROW_EXCEPTION(Logger::varargs_to_string(                        \
        "Failed to compare!",                                         \
        "Expected less than: " + std::to_string(shouldBeMoreOrEqual), \
        "But got: " + std::to_string(is)));                           \
  }

#define THROW_FILE_EXCEPTION(message, filePath) throw FileException(message, LOGGER_GET_LINE, filePath)

#define THROW_EXCEPTION_IF_FILE_MISSING(pathToFile)    \
  if (!std::filesystem::is_regular_file(pathToFile))   \
  {                                                    \
    THROW_FILE_EXCEPTION(                              \
        Logger::varargs_to_string("File is missing!"), \
        pathToFile);                                   \
  }

#define THROW_FILE_EXCEPTION_READ(pathToFile, fromIndex, chunkSize, errCode) \
  THROW_FILE_EXCEPTION(                                                      \
      Logger::varargs_to_string(                                             \
          "Failed to read from file!",                                       \
          "From index: " + std::to_string(fromIndex),                        \
          "Chunk size: " + std::to_string(chunkSize),                        \
          "Write error code: " + std::to_string(errCode)),                   \
      pathToFile);

#define THROW_FILE_EXCEPTION_WRITE(pathToFile, errCode)    \
  THROW_FILE_EXCEPTION(                                    \
      Logger::varargs_to_string(                           \
          "Failed to write to file!",                      \
          "Write error code: " + std::to_string(errCode)), \
      pathToFile);

// -------------------------------------------------
// Declarations
// -------------------------------------------------

class ExceptionHandling
{
private:
  static void terminate_unhandled_exception();

public:
  static void init();
};

class BaseException : public std::runtime_error
{
protected:
  const std::string metadata;
  const std::string DEFAULT_MSG = "Thrown a runtime exception!";

public:
  BaseException(const std::string &message, const std::string &metadata)
      : std::runtime_error(message), metadata(metadata) {}

  virtual void log() const
  {
    Logger::get_instance().log_error(metadata, DEFAULT_MSG, what());
  }

  void log_unhandled() const
  {
    Logger::get_instance().log_error("Unhanddled error!");
    log();
  }
};

class FileException : public BaseException
{
  const std::string DEFAULT_MSG = "Thrown a runtime file exception: ";
  const std::string filePath;

public:
  FileException(
      const std::string &message,
      const std::string &metadata,
      const std::string &filePath)
      : BaseException(message, metadata), filePath(filePath) {}

  void log() const
  {
    Logger::get_instance().log_error(metadata, DEFAULT_MSG + filePath, what());
  }
};

class UserViewException : public BaseException
{
public:
  UserViewException(const std::string &message)
      : BaseException(message, "") {}

  virtual void log() const override
  {
    Logger::get_instance().log_error(what());
  }
};

#endif