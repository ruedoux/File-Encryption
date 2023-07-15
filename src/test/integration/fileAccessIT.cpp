#include <gtest/gtest.h>
#include <fileAccess.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
}

struct FileAccessIT : public ::testing::Test
{
  virtual void SetUp() override
  {
    std::filesystem::create_directory(TEST_FOLDER);
    srand(time(NULL));
  }

  virtual void TearDown() override
  {
    std::filesystem::remove_all(TEST_FOLDER);
  }
};

TEST_F(FileAccessIT, create_delete_and_check_file_exist)
{
  // Given
  std::string filePath = TEST_FOLDER + "/test.txt";

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
  std::string dirPath = TEST_FOLDER + "/test";

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
