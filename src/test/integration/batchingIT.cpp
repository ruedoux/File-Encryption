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

TEST_F(BatchingIT, write_and_read_single_exact_chunk_from_file)
{
  // Given
  DataChunk chunk =
      ChunkFactory::get_chunk(
          Encryption::get_random_bytes(DataChunk::DATA_BYTE_SIZE));
  const u64 fromIndex = 0;

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);
  Batching::append_chunk_to_file(TEST_FILE_PATH, chunk);
  DataChunk readchunk = Batching::read_chunk_from_file<DataChunk>(
      TEST_FILE_PATH, fromIndex, DataChunk::DATA_BYTE_SIZE);

  // Then
  ASSERT_TRUE(createdFile);
  ASSERT_EQ(
      chunk.get_entire_chunk(),
      readchunk.get_entire_chunk());
}

TEST_F(BatchingIT, write_and_read_multiple_chunks_from_file)
{
  // Given
  const u64 repeats = RANDOM_NUMBER(5, 10);
  std::vector<DataChunk> chunks;
  std::vector<DataChunk> readChunks;

  for (u64 i = 0; i < repeats; i++)
  {
    chunks.push_back(
        ChunkFactory::get_chunk(
            Encryption::get_random_bytes(DataChunk::DATA_BYTE_SIZE)));
  }

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);

  for (u64 i = 0; i < repeats; i++)
  {
    Batching::append_chunk_to_file(TEST_FILE_PATH, chunks.at(i));
  }

  for (u64 i = 0; i < repeats; i++)
  {
    readChunks.push_back(
        Batching::read_chunk_from_file<DataChunk>(
            TEST_FILE_PATH, i, DataChunk::DATA_BYTE_SIZE));
  }

  // Then
  ASSERT_TRUE(createdFile);
  for (size_t i = 0; i < chunks.size(); i++)
  {
    ASSERT_EQ(chunks[i].get_entire_chunk(), readChunks[i].get_entire_chunk());
  }
}
