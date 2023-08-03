#include "global.h"

u64 Global::get_random_u64(u64 from, u64 to)
{
  std::random_device rd;
  std::uniform_int_distribution<u64> distribution(from, to);
  return distribution(rd);
}

i64 Global::get_random_i64(i64 from, i64 to)
{
  std::random_device rd;
  std::uniform_int_distribution<i64> distribution(from, to);
  return distribution(rd);
}

std::string Global::str_to_lower(const std::string &str)
{
  std::string lowerCaseStr;
  for (size_t i = 0; i < str.length(); i++)
  {
    lowerCaseStr.push_back(std::tolower(str[i]));
  }
  return lowerCaseStr;
}