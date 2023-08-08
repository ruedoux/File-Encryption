#include <gtest/gtest.h>
#include <Cli/consoleRunner.h>
#include <cstring>

namespace
{
  void encrypt_file(
      const std::filesystem::path &inputFilePath,
      const std::filesystem::path &outputFilePath,
      const std::filesystem::path &passwordFilePath)
  {
    char *inputPathStr = strdup(inputFilePath.string().c_str());
    char *outputPathStr = strdup(outputFilePath.string().c_str());
    char *passwordPathStr = strdup(passwordFilePath.string().c_str());

    int argc = 8;
    char *argv[] = {
        (char *)"exeFileName",
        (char *)"encryptfile",
        (char *)"-i",
        inputPathStr,
        (char *)"-o",
        outputPathStr,
        (char *)"-fp",
        passwordPathStr};

    ConsoleRunner consoleRunner(argc, argv);
    consoleRunner.run();
    free(inputPathStr);
    free(outputPathStr);
    free(passwordPathStr);
  }

  void decrypt_file(
      const std::filesystem::path &inputFilePath,
      const std::filesystem::path &outputFilePath,
      const std::filesystem::path &passwordFilePath)
  {
    char *inputPathStr = strdup(inputFilePath.string().c_str());
    char *outputPathStr = strdup(outputFilePath.string().c_str());
    char *passwordPathStr = strdup(passwordFilePath.string().c_str());

    int argc = 8;
    char *argv[] = {
        (char *)"exeFileName",
        (char *)"decryptfile",
        (char *)"-i",
        inputPathStr,
        (char *)"-o",
        outputPathStr,
        (char *)"-fp",
        passwordPathStr};

    ConsoleRunner consoleRunner(argc, argv);
    consoleRunner.run();
    free(inputPathStr);
    free(outputPathStr);
    free(passwordPathStr);
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
  const std::filesystem::path encryptedFilePath = "cryptedFile";
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

  encrypt_file(sourceFilePath, encryptedFilePath, passwordFilePath);
  decrypt_file(encryptedFilePath, decryptedFilePath, passwordFilePath);

  std::vector<BYTE> decryptedBytes;
  FileAccess::read_bytes_from_file(
      decryptedFilePath, decryptedBytes, 0, FileAccess::get_file_size(decryptedFilePath));

  // Then
  ASSERT_TRUE(createdPasswordFile);
  ASSERT_EQ(FileAccess::ErrorCode::OK, appendedPasswordBytes);
  ASSERT_TRUE(createdSourceFile);
  ASSERT_EQ(FileAccess::ErrorCode::OK, appendedSourceBytes);
  ASSERT_EQ(sourceBytes, decryptedBytes);
}