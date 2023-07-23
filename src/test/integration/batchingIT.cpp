#include <gtest/gtest.h>
#include <batching/batching.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
  const std::string TEST_FILE_NAME = "File";
  const std::string TEST_FILE_PATH = TEST_FOLDER + "/" + TEST_FILE_NAME;
}

struct BatchingIT : public ::testing::Test
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

/*
TEST_F(BatchingIT, write_and_read_single_chunk_from_file)
{
  // Given
  DataChunk dataChunk =
      chunkFactory::get_DataChunk(
          Encryption::get_random_bytes(DataChunk::DATA_BYTE_SIZE));

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);
  bool writtenToFile = Batching::append_chunk_to_file(TEST_FILE_PATH, dataChunk);
  DataChunk readDataChunk = Batching::read_data(TEST_FILE_PATH, 0);

  // Then
  ASSERT_TRUE(createdFile);
  ASSERT_TRUE(writtenToFile);
  ASSERT_EQ(dataChunk, readDataChunk);
}

TEST_F(BatchingIT, write_and_read_multiple_chunks_from_file)
{
  // Given
  const u64 repeats = RANDOM_NUMBER(5, 10);
  std::vector<DataChunk> dataChunks;
  std::vector<DataChunk> readDataChunks;

  for (u64 i = 0; i < repeats; i++)
  {
    dataChunks.push_back(chunkFactory::get_DataChunk(
        Encryption::get_random_bytes(DataChunk::DATA_BYTE_SIZE)));
  }

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);

  bool writtenToFile = true;
  for (u64 i = 0; i < repeats; i++)
  {
    writtenToFile =
        writtenToFile &&
        Batching::append_chunk_to_file(TEST_FILE_PATH, dataChunks.at(i));
  }

  for (u64 i = 0; i < repeats; i++)
  {
    readDataChunks.push_back(Batching::read_data(TEST_FILE_PATH, i));
  }

  // Then
  ASSERT_TRUE(createdFile);
  ASSERT_TRUE(writtenToFile);
  ASSERT_EQ(dataChunks, readDataChunks);
}
*/