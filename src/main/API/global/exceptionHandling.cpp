#include "exceptionhandling.h"

void ExceptionHandling::terminate_unhandled_exception()
{
  try
  {
    std::rethrow_exception(std::current_exception());
  }
  catch (const BaseException &ex)
  {
    ex.log_unhandled();
  }
  catch (const std::exception &ex)
  {
    std::cerr << "Unhandled basic exception: " << ex.what() << std::endl;
  }
}

void ExceptionHandling::init()
{
  std::set_terminate(terminate_unhandled_exception);
}
