#include "timer.h"

Timer::Timer() { Timer::start(); }

void Timer::start() { s = std::chrono::steady_clock::now(); }

i64 Timer::get_ms_since_start()
{
  e = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
}

void Timer::sleep(i32 sleepTime)
{
  std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(sleepTime));
}
