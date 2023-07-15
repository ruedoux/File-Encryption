#include "logger.h"

void Logger::log_stdout(
    const std::string &marker,
    const std::string &concatenatedMessage)
{
  static std::mutex stdoutMutex;
  std::lock_guard<std::mutex> lock(stdoutMutex);

  std::cout << marker << concatenatedMessage << _ANSI_RESET << "\n";
}

void Logger::log_stderr(
    const std::string &marker,
    const std::string &concatenatedMessage)
{
  static std::mutex stderrMutex;
  std::lock_guard<std::mutex> lock(stderrMutex);

  std::cerr << marker << concatenatedMessage << _ANSI_RESET << "\n";
}