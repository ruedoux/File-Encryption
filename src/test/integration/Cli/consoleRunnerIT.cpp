#include <gtest/gtest.h>
#include <Cli/consoleRunner.h>

namespace
{
  void encrypt_file(
      const std::filesystem::path &inputFilePath,
      const std::filesystem::path &outputFilePath,
      const std::filesystem::path &passwordFilePath)
  {
    int argc = 7;
    char *argv[] = {
        (char *)"exeFileName",
        (char *)"commandName",
        (char *)"encryptfile",
        (char *)"-i",
        (char *)inputFilePath.c_str(),
        (char *)"-o",
        (char *)outputFilePath.c_str(),
        (char *)"-fp",
        (char *)passwordFilePath.c_str()};
    
    ConsoleRunner consoleRunner(argc, argv);
    consoleRunner.run();
  }

  void decrypt_file(
      const std::filesystem::path &inputFilePath,
      const std::filesystem::path &outputFilePath,
      const std::filesystem::path &passwordFilePath)
  {
    int argc = 7;
    char *argv[] = {
        (char *)"exeFileName",
        (char *)"commandName",
        (char *)"decryptfile",
        (char *)"-i",
        (char *)inputFilePath.c_str(),
        (char *)"-o",
        (char *)outputFilePath.c_str(),
        (char *)"-fp",
        (char *)passwordFilePath.c_str()};
    
    ConsoleRunner consoleRunner(argc, argv);
    consoleRunner.run();
  }
}

struct ConsoleRunnerIT : public ::testing::Test
{
  virtual void SetUp() override {}

  virtual void TearDown() override {}
};

TEST_F(ConsoleRunnerIT, test_crypt_and_decrypt_file)
{
  // Given

  // When

  // Then
}