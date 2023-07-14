#include "main/global/logger.h"

int main(int argc, char *argv[])
{
  PRINTLN("asss");
  Logger::log_info(LOGGER_GET_LINE, "This is a message");
  return 0;
}
