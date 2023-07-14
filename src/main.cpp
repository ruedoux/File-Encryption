#include "main/global/logger.h"

int main(int argc, char *argv[])
{
  Logger::log_info(LOGGER_GET_LINE, "This is a message");
  Logger::log_info("This is a message");
  Logger::log_error("Exceptional");
  Logger::log("This is normal");
  return 0;
}
