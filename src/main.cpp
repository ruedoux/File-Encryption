#include <Cli/ConsoleCommands.h>

int main(int argc, char *argv[])
{
  std::vector<std::string> args;
  if (argc < 2)
  {
    ConsoleCommands::run_command("help", args);
  }

  for (int i = 2; i < argc; i++)
  {
    args.push_back(GLOBAL::str_to_lower(static_cast<std::string>(argv[i])));
  }

  ConsoleCommands::run_command(
      GLOBAL::str_to_lower(static_cast<std::string>(argv[1])), args);

  return EXIT_SUCCESS;
}
