#include <global/utils/logger.h>

int main(int argc, char *argv[])
{
  Logger& logger = Logger::get_instance();
  logger.log_info(LOGGER_GET_LINE, "This is a message");
  logger.log_info("This is a message");
  logger.log_error("Exceptional");
  logger.log("This is normal");
  return 0;
}
