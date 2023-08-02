#include <gtest/gtest.h>
#include <Cli/commandConsumer/argumentParser/argumentParser.h>

namespace
{

}

struct ArgumentParserTest : public ::testing::Test
{
  virtual void SetUp() override {}

  virtual void TearDown() override {}
};

TEST_F(ArgumentParserTest, parse_argument_options_when_exact)
{
  // Given
  const std::vector<std::string> args(
      {"-d", "commandD", "-f", "commandF"});

  // When
  const std::unordered_map<std::string, std::string> parsedArgsOptions =
      ArgumentParser::parse_args_options(args);

  // Then
  ASSERT_EQ(parsedArgsOptions.at("-d"), "commandD");
  ASSERT_EQ(parsedArgsOptions.at("-f"), "commandF");
}

TEST_F(ArgumentParserTest, parse_argument_options_when_random)
{
  // Given
  const std::vector<std::string> args(
      {"xxxx", "xxxx", "-d", "commandD", "xxxx", "-f", "commandF", "xxxx"});

  // When
  const std::unordered_map<std::string, std::string> parsedArgsOptions =
      ArgumentParser::parse_args_options(args);

  // Then
  ASSERT_EQ(parsedArgsOptions.at("-d"), "commandD");
  ASSERT_EQ(parsedArgsOptions.at("-f"), "commandF");
}

TEST_F(ArgumentParserTest, return_empty_if_no_options)
{
  // Given
  const std::vector<std::string> args({"xxxx"});

  // When
  const std::unordered_map<std::string, std::string> parsedArgsOptions =
      ArgumentParser::parse_args_options(args);

  // Then
  ASSERT_TRUE(parsedArgsOptions.empty());
}