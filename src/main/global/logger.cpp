#include "logger.h"

namespace
{
// Ansi colors
#define _BOLD "\033[1m"
#define _RED "\033[31m"
#define _GREEN "\033[32m"
#define _BLUE "\033[34m"
#define _ANSI_RESET "\033[0m"
}

void Logger::log_stdout(
    const std::string &marker,
    const std::string &concatenatedMessage)
{
  std::cout << _BOLD << _BLUE << marker << " ";
  std::cout << concatenatedMessage << _ANSI_RESET << "\n";
}

void Logger::log_stderr(
    const std::string &marker,
    const std::string &concatenatedMessage)
{
  std::cerr << _BOLD << _RED << marker << " ";
  std::cerr << concatenatedMessage << _ANSI_RESET << "\n";
}