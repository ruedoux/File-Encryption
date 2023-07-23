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

#define RANDOM_NUMBER(min, max) [](auto from, auto to) \
{ std::random_device rd;                                      \
  std::uniform_int_distribution<BYTE> distribution(from, to); \
  return distribution(rd); }(min, max)

#define KiB(x) ((size_t)(x) << 10) // Binary kilobyte
#define MiB(x) ((size_t)(x) << 20) // Binary megabyte
#define GiB(x) ((size_t)(x) << 30) // Binary gigabyte

#define BYTE u8
#define BYTE_SIZE std::sizeof(u8)
#define BYTE_MAX_VALUE 255
#define BYTE_MIN_VALUE 0

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

#endif
