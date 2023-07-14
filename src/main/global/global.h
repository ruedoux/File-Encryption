// -------------------------------------------------
// Header included in all files (global includes and typedefs)
// -------------------------------------------------

#pragma once
#ifndef MAIN_GLOBAL
#define MAIN_GLOBAL

// -------------------------------------------------
// DEPENDENCIES
// -------------------------------------------------

// C libs
#include <time.h>
#include <cmath>

// C++ STD
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include <functional> // Function pointers
#include <limits>     // Overflow management

// C++ STL
#include <unordered_map>
#include <vector>

// -------------------------------------------------
// MACROS
// -------------------------------------------------

#define PRINTLN(x) std::cout << x << "\n"
#define PRINT(x) std::cout << x

#define KiB(x) ((size_t)(x) << 10) // Binary kilobyte
#define MiB(x) ((size_t)(x) << 20) // Binary megabyte
#define GiB(x) ((size_t)(x) << 30) // Binary gigabyte

#define BYTE u8
#define BYTE_SIZE sizeof(u8)
#define BYTE_MAX_VALUE 255

#ifdef _MSC_VER
#define THIS_FUNCTION __FUNCSIG__
#else
#define THIS_FUNCTION __PRETTY_FUNCTION__
#endif

// -------------------------------------------------
// GLOBAL TYPEDEFS
// -------------------------------------------------

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

// -------------------------------------------------
// DECLARATION
// -------------------------------------------------

namespace GLOBAL
{
  std::string convert_bytes_to_string(const std::vector<BYTE> bytes);
  std::vector<BYTE> convert_string_to_bytes(const std::string str);
  std::string str_to_lower(std::string str);
  void print_bytes(const std::vector<BYTE> bytes);
  f64 round_up_number(f64 value, u32 places);

  template <typename T>
  bool check_multiplication_overflow(T a, T b)
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
  T get_random_number(T from, T to)
  {
    T n = to - from + 1;
    T i = rand() % n;
    if (i < 0)
      i = -i;
    return from + i;
  }
}

#endif
