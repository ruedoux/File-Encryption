#include "logger.h"

void Logger::log_stdout(
    const std::string &marker,
    const std::string &concatenatedMessage)
{
  std::cout << marker << concatenatedMessage << _ANSI_RESET << "\n";
}

void Logger::log_stderr(
    const std::string &marker,
    const std::string &concatenatedMessage)
{
  std::cerr << marker << concatenatedMessage << _ANSI_RESET << "\n";
}