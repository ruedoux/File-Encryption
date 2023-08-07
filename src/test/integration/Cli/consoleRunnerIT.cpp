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

TEST_F(ConsoleRunnerIT, test_crypt_and_decrypt_file_small)
{
  // Given
  const std::filesystem::path passwordFilePath = "passwordFile";
  const std::filesystem::path sourceFilePath = "sourceFile";
  const std::filesystem::path cryptedFilePath = "cryptedFile";
  const std::filesystem::path decryptedFilePath = "decryptedFile";

  const std::vector<BYTE> password = Encryption::get_random_bytes(
      Global::get_random_u64(4, Encryption::KEY_BYTE_SIZE));
  const std::vector<BYTE> sourceBytes = Encryption::get_random_bytes(
      Global::get_random_u64(1, Encryption::KEY_BYTE_SIZE));

  // When
  const bool createdPasswordFile = FileAccess::create_file(passwordFilePath);
  const FileAccess::ErrorCode appendedPasswordBytes =
      FileAccess::append_bytes_to_file(passwordFilePath, password);
  const bool createdSourceFile = FileAccess::create_file(sourceFilePath);
  const FileAccess::ErrorCode appendedSourceBytes =
      FileAccess::append_bytes_to_file(sourceFilePath, sourceBytes);
  
  

  // Then
  ASSERT_TRUE(createdPasswordFile);
  ASSERT_EQ(FileAccess::ErrorCode::OK, appendedPasswordBytes);
  ASSERT_TRUE(createdSourceFile);
  ASSERT_EQ(FileAccess::ErrorCode::OK, appendedSourceBytes);
}