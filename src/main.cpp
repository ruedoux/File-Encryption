#include "main/global/logger.h"

int main(int argc, char *argv[])
{
  PRINTLN("asss");
  Logger::log_info("First", "Second");
  return 0;
}
