#include <gtest/gtest.h>
#include <batching/batching.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
  const std::string TEST_FILE_NAME = "File";
  const std::string TEST_FILE_PATH = TEST_FOLDER + "/" + TEST_FILE_NAME;

  bool write_bytes_to_file(const std::string &filePath, std::vector<BYTE> bytes)
  {
    ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, false);

    std::ofstream file(filePath, Batching::WRITE_APPEND_OPEN_MODE);
    ERROR_RETURN_IF_FILE_NOT_OPEN(file, filePath, false);

    ERROR_RETURN_IF_FILE_OPERATION_FAILED(
        file.write(reinterpret_cast<const char *>(bytes.data()), bytes.size()),
        false,
        "Failed to write append to file: ", filePath,
        ", data size: ", std::to_string(bytes.size()))

    return true;
  }
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

TEST_F(BatchingIT, write_and_read_single_chunk_from_file)
{
  // Given
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(
          Encryption::get_random_bytes(DataChunk::CHUNK_BYTE_SIZE));

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);
  bool writtenToFile = Batching::write_append_chunk(TEST_FILE_PATH, dataChunk);
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
    dataChunks.push_back(DataChunkFactory::get_DataChunk(
        Encryption::get_random_bytes(DataChunk::CHUNK_BYTE_SIZE)));
  }

  // When
  bool createdFile = FileAccess::create_file(TEST_FILE_PATH);

  bool writtenToFile = true;
  for (u64 i = 0; i < repeats; i++)
  {
    writtenToFile =
        writtenToFile &&
        Batching::write_append_chunk(TEST_FILE_PATH, dataChunks.at(i));
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

TEST_F(BatchingIT, should_correctly_count_chunks_in_file)
{
  // Given
  const std::string filePathLess = TEST_FILE_PATH + "1";
  const std::string filePathExactly = TEST_FILE_PATH + "2";
  const std::string filePathMore = TEST_FILE_PATH + "3";

  // When
  bool createdFileLess = FileAccess::create_file(filePathLess);
  bool createdFileExactly = FileAccess::create_file(filePathExactly);
  bool createdFileMore = FileAccess::create_file(filePathMore);

  bool writtenFileLess = write_bytes_to_file(
      filePathLess,
      Encryption::get_random_bytes(DataChunk::CHUNK_BYTE_SIZE - 1));
  bool writtenFileExactly = write_bytes_to_file(
      filePathExactly,
      Encryption::get_random_bytes(DataChunk::CHUNK_BYTE_SIZE));
  bool writtenFileMore = write_bytes_to_file(
      filePathMore,
      Encryption::get_random_bytes(DataChunk::CHUNK_BYTE_SIZE + 1));
  
  u64 chunkCountLess = Batching::get_chunk_count_in_file(filePathLess);
  u64 chunkCountExactly = Batching::get_chunk_count_in_file(filePathExactly);
  u64 chunkCountMore = Batching::get_chunk_count_in_file(filePathMore);

  // Then
  ASSERT_TRUE(createdFileLess);
  ASSERT_TRUE(createdFileExactly);
  ASSERT_TRUE(createdFileMore);

  ASSERT_TRUE(writtenFileLess);
  ASSERT_TRUE(writtenFileExactly);
  ASSERT_TRUE(writtenFileMore);

  ASSERT_EQ(1, chunkCountLess);
  ASSERT_EQ(1, chunkCountExactly);
  ASSERT_EQ(2, chunkCountMore);
}