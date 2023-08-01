// -------------------------------------------------
// Header included in all files (global includes and typedefs)
// -------------------------------------------------

#pragma once
#ifndef MAIN_GLOBAL
#define MAIN_GLOBAL

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

// C++ STD
#include <algorithm>
#include <atomic>
#include <mutex>
#include <random>
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include <functional>
#include <limits>
#include <unordered_map>
#include <vector>
#include <sstream>

// -------------------------------------------------
// Macros
// -------------------------------------------------

#define KiB(x) ((size_t)(x) << 10) // Binary kilobyte
#define MiB(x) ((size_t)(x) << 20) // Binary megabyte
#define GiB(x) ((size_t)(x) << 30) // Binary gigabyte

#define BYTE u8
#define BYTE_SIZE std::sizeof(u8)
#define BYTE_MAX_VALUE 255
#define BYTE_MIN_VALUE 0

#ifdef _MSC_VER
#define THIS_FUNCTION __FUNCSIG__
#else
#define THIS_FUNCTION __PRETTY_FUNCTION__
#endif

// -------------------------------------------------
// Typedefs
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
// Global functions
// -------------------------------------------------

namespace GLOBAL
{
  static u64 get_random_u64(u64 from, u64 to)
  {
    std::random_device rd;
    std::uniform_int_distribution<u64> distribution(from, to);
    return distribution(rd);
  }

  static i64 get_random_i64(i64 from, i64 to)
  {
    std::random_device rd;
    std::uniform_int_distribution<i64> distribution(from, to);
    return distribution(rd);
  }

  static std::string str_to_lower(const std::string &str)
  {
    std::string lowerCaseStr;
    for (size_t i = 0; i < str.length(); i++)
    {
      lowerCaseStr.push_back(std::tolower(str[i]));
    }
    return lowerCaseStr;
  }
}

#endif
