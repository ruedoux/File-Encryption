#include <gtest/gtest.h>
#include <Api/batching/fileAccess/fileAccess.h>
#include <Api/batching/chunkEncryption/dataChunk/encryption/encryption.h>

namespace
{
  const std::filesystem::path TEST_FOLDER = "TESTS";
}

struct FileAccessTest : public ::testing::Test
{
  virtual void SetUp() override
  {
    std::filesystem::create_directory(TEST_FOLDER);
  }

  virtual void TearDown() override
  {
    std::filesystem::remove_all(TEST_FOLDER);
  }
};

TEST_F(FileAccessTest, create_file)
{
  // Given
  const std::filesystem::path filePath = TEST_FOLDER / "test.txt";

  // When
  bool createdFile = FileAccess::create_file(filePath);

  // Then
  ASSERT_TRUE(std::filesystem::is_regular_file(filePath));
  ASSERT_TRUE(createdFile);
}

TEST_F(FileAccessTest, create_dir)
{
  // Given
  const std::filesystem::path folderPath = TEST_FOLDER / "test";

  // When
  bool createdFolder = FileAccess::create_dir(folderPath);

  // Then
  ASSERT_TRUE(std::filesystem::is_directory(folderPath));
  ASSERT_TRUE(createdFolder);
}

TEST_F(FileAccessTest, delete_file)
{
  // Given
  const std::filesystem::path filePath = TEST_FOLDER / "test.txt";

  // When
  std::fstream file(filePath, std::fstream::out);
  file.close();

  bool deletedFile = FileAccess::delete_file(filePath);

  // Then
  ASSERT_FALSE(std::filesystem::exists(filePath));
  ASSERT_TRUE(deletedFile);
}

TEST_F(FileAccessTest, delete_dir)
{
  // Given
  const std::filesystem::path folderPath = TEST_FOLDER / "test";

  // When
  std::filesystem::create_directory(folderPath);
  bool deletedFolder = FileAccess::delete_dir(folderPath);

  // Then
  ASSERT_FALSE(std::filesystem::is_directory(folderPath));
  ASSERT_TRUE(deletedFolder);
}

TEST_F(FileAccessTest, file_exist)
{
  // Given
  const std::filesystem::path filePath = TEST_FOLDER / "test.txt";
  const std::string wrongFilePath = "doesntexist";

  // When
  std::fstream file(filePath, std::fstream::out);
  file.close();

  // Then
  ASSERT_TRUE(FileAccess::file_exist(filePath));
  ASSERT_FALSE(FileAccess::file_exist(wrongFilePath));
}

TEST_F(FileAccessTest, dir_exist)
{
  // Given
  const std::filesystem::path folderPath = TEST_FOLDER / "test";
  const std::string wrongfolderPath = "doesntexist";

  // When
  std::filesystem::create_directory(folderPath);

  // Then
  ASSERT_TRUE(FileAccess::dir_exist(folderPath));
  ASSERT_FALSE(FileAccess::dir_exist(wrongfolderPath));
}

TEST_F(FileAccessTest, get_byte_count_left_in_file)
{
  // Given
  static constexpr u64 baseFileSize = 123;
  const std::filesystem::path filePath = TEST_FOLDER / "test.txt";
  u64 bytesLeft = Global::get_random_u64(0, 1000);
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      baseFileSize + bytesLeft);

  // When
  bool createdFile = FileAccess::create_file(filePath);
  FileAccess::ErrorCode appended = FileAccess::append_bytes_to_file(
      filePath, bytes);

  u64 bytesLeftResult = FileAccess::get_byte_count_left_in_file(
      filePath, baseFileSize);

  // Then
  ASSERT_EQ(bytesLeft, bytesLeftResult);
}

TEST_F(FileAccessTest, append_bytes_to_file)
{
  // Given
  const std::filesystem::path filePath = TEST_FOLDER / "test.txt";
  const std::vector<BYTE> bytesInFile = Encryption::get_random_bytes(
      Global::get_random_u64(MiB(1), MiB(3)));

  // When
  bool createdFile = FileAccess::create_file(filePath);
  FileAccess::ErrorCode appendedToFile = FileAccess::append_bytes_to_file(
      filePath, bytesInFile);

  // Then
  ASSERT_TRUE(createdFile);
  ASSERT_EQ(FileAccess::ErrorCode::OK, appendedToFile);
  ASSERT_EQ(bytesInFile.size(), std::filesystem::file_size(filePath));
}