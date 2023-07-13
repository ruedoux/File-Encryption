// -------------------------------------------------
// Header included in all files (global includes and typedefs)
// -------------------------------------------------

#pragma once
#ifndef TIMER_GLOBAL
#define TIMER_GLOBAL

// -------------------------------------------------
// DEPENDENCIES
// -------------------------------------------------

#include "global.h"
#include <chrono>
#include <thread>

// -------------------------------------------------
// DECLARATIONS
// -------------------------------------------------

class Timer
{
private:
  std::chrono::steady_clock::time_point s;
  std::chrono::steady_clock::time_point e;

public:
  Timer();

  void start();
  i64 get_ms_since_start();
  static void sleep(i32 sleepTime);
};

#endif