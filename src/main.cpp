#include <Cli/ConsoleRunner.h>

int main(int argc, char *argv[])
{
  ConsoleRunner consoleCommands(argc, argv);
  consoleCommands.run();
  return EXIT_SUCCESS;
}
