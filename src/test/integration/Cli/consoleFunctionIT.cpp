#include <gtest/gtest.h>
#include <Cli/functionLibrary/consoleFunction/consoleFunction.h>

namespace
{
  bool wasFunctionTriggered = false;

  static void test_function(const ArgumentConsumer &argumentConsumer)
  {
    wasFunctionTriggered = true;
  }
}

struct ConsoleFunctionIT : public ::testing::Test
{
  virtual void SetUp() override 
  {
    wasFunctionTriggered = false;
  }

  virtual void TearDown() override 
  {
    wasFunctionTriggered = false;
  }
};

TEST_F(ConsoleFunctionIT, should_correctly_map_input)
{
  ConsoleFunction consoleFunction(&test_function, "test");
  
}