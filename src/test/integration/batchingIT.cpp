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
  ChunkContainer<DataChunk> chunkContainer =
      ChunkFactory::get_chunk(
          Encryption::get_random_bytes(DataChunk::DATA_BYTE_SIZE));
  u64 fromIndex = 0;

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);
  bool writtenToFile = Batching::append_chunk_to_file(
      TEST_FILE_PATH, chunkContainer);
  ChunkContainer<DataChunk> readChunkContainer =
      Batching::read_chunk_from_file<DataChunk>(TEST_FILE_PATH, fromIndex);

  // Then
  ASSERT_TRUE(createdFile);
  ASSERT_TRUE(writtenToFile);
  ASSERT_TRUE(!readChunkContainer.is_error());
  ASSERT_EQ(
      chunkContainer.get_result().get_entire_chunk(),
      readChunkContainer.get_result().get_entire_chunk());
}

TEST_F(BatchingIT, write_and_read_multiple_chunks_from_file)
{
  // Given
  const u64 repeats = RANDOM_NUMBER(5, 10);
  std::vector<ChunkContainer<DataChunk>> chunkContainers;
  std::vector<ChunkContainer<DataChunk>> readChunkContainers;

  for (u64 i = 0; i < repeats; i++)
  {
    chunkContainers.push_back(ChunkFactory::get_chunk(
        Encryption::get_random_bytes(DataChunk::DATA_BYTE_SIZE)));
  }

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);

  bool writtenToFile = true;
  for (u64 i = 0; i < repeats; i++)
  {
    writtenToFile =
        writtenToFile &&
        Batching::append_chunk_to_file(TEST_FILE_PATH, chunkContainers.at(i));
  }

  for (u64 i = 0; i < repeats; i++)
  {
    readChunkContainers.push_back(
        Batching::read_chunk_from_file<DataChunk>(TEST_FILE_PATH, i));
  }

  // Then
  ASSERT_TRUE(createdFile);
  ASSERT_TRUE(writtenToFile);
  for (size_t i = 0; i < chunkContainers.size(); i++)
  {
    ASSERT_EQ(
        chunkContainers[i].get_result().get_entire_chunk(),
        readChunkContainers[i].get_result().get_entire_chunk());
  }
}
*/