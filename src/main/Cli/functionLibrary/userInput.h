#pragma once

#ifndef USER_INPUT
#define USER_INPUT

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <API/global/logger.h>

// --------------------------------------------
// Macros
// --------------------------------------------

namespace
{
#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <unistd.h>
#include <termios.h>
#endif

#ifdef _WIN32
#define ENTER_KEY (char)13
#elif __linux__
#define ENTER_KEY (char)10
  char getch()
  {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
    {
      return '\0';
    }
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
    {
      return '\0';
    }
    if (read(0, &buf, 1) < 0)
    {
      return '\0';
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
    {
      return '\0';
    }
    return buf;
  }
#endif
}

class UserInput
{
public:
  static std::string get_input_from_console_hidden(
      const std::string &promptMessage,
      const bool showStars = false)
  {
    std::cout << promptMessage;

    std::string input;
    char ch;
    while ((ch = getch()) != ENTER_KEY)
    {
      if (ch == '\0')
      {
        return std::string();
      }

      if (ch == '\b')
      {
        if (input.size() > 0)
        {
          input.pop_back();
          if (showStars)
          {
            std::cout << '\b' << ' ' << '\b';
          }
        }
        continue;
      }

      input.push_back(ch);
      if (showStars)
      {
        std::cout << "*";
      }
    }

    std::cout << "\n";
    return input;
  }

  static std::vector<BYTE> string_to_bytes(const std::string &in)
  {
    std::vector<BYTE> out;
    for (char ch : in)
    {
      out.push_back(static_cast<BYTE>(ch));
    }

    return out;
  }

  static std::vector<BYTE> get_input_from_console_hidden_as_bytes(
      const std::string &promptMessage,
      const bool showStars = false)
  {
    return string_to_bytes(get_input_from_console_hidden(promptMessage, showStars));
  }
};

#endif