#include <gtest/gtest.h>
#include <main/fileAccess.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
}

struct FileAccessTest : public ::testing::Test
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

TEST_F(FileAccessTest, create_file)
{
  // Given
  std::string filePath = TEST_FOLDER + "/test.txt";

  // When
  bool createdFile = FileAccess::create_file(filePath);

  // Then
  ASSERT_TRUE(std::filesystem::is_regular_file(filePath));
  ASSERT_TRUE(createdFile);
}

TEST_F(FileAccessTest, create_dir)
{
  // Given
  std::string folderPath = TEST_FOLDER + "/test";

  // When
  bool createdFolder = FileAccess::create_dir(folderPath);

  // Then
  ASSERT_TRUE(std::filesystem::is_directory(folderPath));
  ASSERT_TRUE(createdFolder);
}

TEST_F(FileAccessTest, delete_file)
{
  // Given
  std::string filePath = TEST_FOLDER + "/test.txt";

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
  std::string folderPath = TEST_FOLDER + "/test";

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
  std::string filePath = TEST_FOLDER + "/test.txt";
  std::string wrongFilePath = "doesntexist";

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
  std::string folderPath = TEST_FOLDER + "/test";
  std::string wrongfolderPath = "doesntexist";

  // When
  std::filesystem::create_directory(folderPath);

  // Then
  ASSERT_TRUE(FileAccess::dir_exist(folderPath));
  ASSERT_FALSE(FileAccess::dir_exist(wrongfolderPath));
}