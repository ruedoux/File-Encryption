#include <Cli/ConsoleRunner.h>

int main(int argc, char *argv[])
{
  ExceptionHandling::init();

  try
  {
    ConsoleRunner consoleCommands(argc, argv);
    consoleCommands.run();
  }
  catch (const BaseException &ex)
  {
    ex.log();
  }

  return EXIT_SUCCESS;
}
