#include <global/exceptionHandling.h>

int main(int argc, char *argv[])
{
  ExceptionHandling::init();

  try
  {
    THROW_EXCEPTION_IF_NOT_MATCH(6,5);
  }
  catch (const BaseException &e)
  {
    e.log();
  }

  return 0;
}
