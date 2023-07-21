#include <global/logging/logger.h>

int main(int argc, char *argv[])
{
  Logger& logger = Logger::get_instance();
  logger.log_info("This is multi line", "Should be next line", "And next");
  logger.log_error(LOGGER_GET_LINE, "Error test!", "This is content");
  logger.log("This is normal message", "Should be new line");
  return 0;
}
