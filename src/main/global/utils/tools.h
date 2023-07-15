#pragma once
#ifndef TOOLS_GLOBAL
#define TOOLS_GLOBAL

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

#include <global/global.h>

// -------------------------------------------------
// Definitions
// -------------------------------------------------

class Tools
{
public:
  static std::string convert_bytes_to_string(const std::vector<BYTE> bytes);
  static std::vector<BYTE> convert_string_to_bytes(const std::string str);
  static std::string str_to_lower(std::string str);
  static void print_bytes(const std::vector<BYTE> bytes);
  static f64 round_up_number(f64 value, u32 places);

  template <typename T>
  static bool check_multiplication_overflow(T a, T b)
  {
    constexpr auto maxValue = std::numeric_limits<T>::max();
    constexpr auto minValue = std::numeric_limits<T>::min();

    if (a == -1 && b == minValue)
      return false;
    if (b == -1 && a == minValue)
      return false;

    if (b != 0 && a > maxValue / b)
      return false;
    if (b != 0 && a < minValue / b)
      return false;

    return true;
  }

  template <typename T>
  static T get_random_number(T from, T to)
  {
    T n = to - from + 1;
    T i = rand() % n;
    if (i < 0)
      i = -i;
    return from + i;
  }
};

#endif