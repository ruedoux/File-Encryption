#include <gtest/gtest.h>
#include <API/batching/chunkEncryption/dataChunk/encryption/encryption.h>
#include <API/batching/fileAccess/fileAccess.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
}

struct FileAccessIT : public ::testing::Test
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

TEST_F(FileAccessIT, create_delete_and_check_file_exist)
{
  // Given
  const std::string filePath = TEST_FOLDER + "/test.txt";

  // When
  bool fileExistsBeforeCreation = FileAccess::file_exist(filePath);
  bool fileCreated = FileAccess::create_file(filePath);
  bool fileExisitsWhenCreated = FileAccess::file_exist(filePath);
  bool fileDeleted = FileAccess::delete_file(filePath);
  bool fileExistsAfterDeletion = FileAccess::file_exist(filePath);

  // Then
  ASSERT_FALSE(fileExistsBeforeCreation);
  ASSERT_TRUE(fileCreated);
  ASSERT_TRUE(fileExisitsWhenCreated);
  ASSERT_TRUE(fileDeleted);
  ASSERT_FALSE(fileExistsAfterDeletion);
}

TEST_F(FileAccessIT, create_delete_and_check_folder_exist)
{
  // Given
  const std::string dirPath = TEST_FOLDER + "/test";

  // When
  bool dirExistsBeforeCreation = FileAccess::dir_exist(dirPath);
  bool dirCreated = FileAccess::create_dir(dirPath);
  bool dirExisitsWhenCreated = FileAccess::dir_exist(dirPath);
  bool dirDeleted = FileAccess::delete_dir(dirPath);
  bool dirExistsAfterDeletion = FileAccess::dir_exist(dirPath);

  // Then
  ASSERT_FALSE(dirExistsBeforeCreation);
  ASSERT_TRUE(dirCreated);
  ASSERT_TRUE(dirExisitsWhenCreated);
  ASSERT_TRUE(dirDeleted);
  ASSERT_FALSE(dirExistsAfterDeletion);
}

TEST_F(FileAccessIT, read_and_write_to_file)
{
  // Given
  const std::string filePath = TEST_FOLDER + "/test.txt";
  std::vector<BYTE> bytes = Encryption::get_random_bytes(MiB(2));
  u64 repeats = GLOBAL::get_random_u64(2, 10);

  // When
  bool createdFile = FileAccess::create_file(filePath);

  for (u64 i = 0; i < repeats; i++)
  {
    ASSERT_EQ(
        FileAccess::ErrorCode::OK,
        FileAccess::append_bytes_to_file(filePath, bytes));
  }

  // Then
  for (u64 i = 0; i < repeats; i++)
  {
    std::vector<BYTE> readBytes;
    ASSERT_EQ(
        FileAccess::ErrorCode::OK,
        FileAccess::read_bytes_from_file(
            filePath, readBytes, i * bytes.size(), bytes.size()));
    ASSERT_EQ(bytes, readBytes);
  }

  ASSERT_TRUE(createdFile);
  ASSERT_EQ(bytes.size()*repeats, FileAccess::get_file_size(filePath));
}