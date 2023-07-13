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
  bool createdFile = FileAccess::file_create(filePath);

  // Then
  ASSERT_TRUE(std::filesystem::is_regular_file(filePath));
  ASSERT_TRUE(createdFile);
}

TEST_F(FileAccessTest, delete_file)
{
  // Given
  std::string filePath = TEST_FOLDER + "/test.txt";

  // When
  std::fstream file(filePath, std::fstream::out);
  file.close();
  
  bool deletedFile = FileAccess::file_delete(filePath);

  // Then
  ASSERT_FALSE(std::filesystem::exists(filePath));
  ASSERT_TRUE(deletedFile);
}