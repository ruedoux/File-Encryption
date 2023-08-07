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
  // Given
  ConsoleFunction consoleFunction(&test_function, "test");
  const std::string description = "desc";
  const std::string option = "-o";
  const std::string optionDescription = "output";

  // When
  consoleFunction.run_bound_function(ArgumentConsumer());
  consoleFunction.add_description(description);
  consoleFunction.add_required_option(option, optionDescription);

  // Then
  ASSERT_EQ(description, consoleFunction.get_description());
  ASSERT_EQ(optionDescription, consoleFunction.get_required_option(option));
  ASSERT_TRUE(wasFunctionTriggered);
}