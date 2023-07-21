#include "logger.h"

void Logger::log_stdout(const std::string &concatenatedMessage)
{
  static std::mutex stdoutMutex;
  std::lock_guard<std::mutex> lock(stdoutMutex);

  std::cout << concatenatedMessage << _ANSI_RESET;
}

void Logger::log_stderr(const std::string &concatenatedMessage)
{
  static std::mutex stderrMutex;
  std::lock_guard<std::mutex> lock(stderrMutex);

  std::cerr << concatenatedMessage << _ANSI_RESET;
}

std::string Logger::format_log(
    const std::string &src,
    const std::string &marker)
{
  std::string formatted;
  for (const char &letter : src)
  {
    formatted += letter;
    if (letter == '\n')
    {
      for (u64 i = 0; i < marker.length(); i++)
      {
        formatted += ' ';
      }
    }
  }

  if(src.back() == '\n')
  {
    formatted = formatted.substr(0, formatted.length() - marker.length());
  }

  return formatted;
}