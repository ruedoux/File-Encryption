// -------------------------------------------------
// DEPENDENCIES
// -------------------------------------------------

#include "global.h"

// -------------------------------------------------
// DEFINITIONS
// -------------------------------------------------

GLOBAL::Timer::Timer() { GLOBAL::Timer::start(); }

void GLOBAL::Timer::start() { s = std::chrono::steady_clock::now(); }

i64 GLOBAL::Timer::get_ms_since_start()
{
  e = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
}

void GLOBAL::Timer::sleep(i32 sleepTime)
{
  std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(sleepTime));
}

std::string GLOBAL::convert_bytes_to_string(const std::vector<BYTE> bytes)
{
  std::string output;
  for (size_t i = 0; i < bytes.size(); i++)
  {
    BYTE byte = bytes[i];
    if (byte > 126)
    {
      byte = 48; // 0
    }
    output.push_back(static_cast<char>(byte));
  }
  return output;
}

std::vector<BYTE> GLOBAL::convert_string_to_bytes(const std::string str)
{
  std::vector<BYTE> bytes;
  for (size_t i = 0; i < str.size(); i++)
  {
    bytes.push_back(static_cast<BYTE>(str[i]));
  }
  return bytes;
}

std::string GLOBAL::str_to_lower(std::string str)
{
  for (size_t i = 0; i < str.length(); i++)
  {
    str[i] = tolower(str[i]);
  }
  return str;
}

void GLOBAL::print_bytes(const std::vector<BYTE> bytes)
{
  for (size_t i = 0; i < bytes.size(); i++)
  {
    PRINT(bytes[i] << " ");
  }
  PRINT("\n");
}

f64 GLOBAL::round_up_number(f64 value, u32 places)
{
  const f64 multiplier = std::pow(10.0, places);
  return std::ceil(value * multiplier) / multiplier;
}