#include <gtest/gtest.h>
#include <batching/chunkEncryption/dataChunk/ChunkFactory.h>

struct DataChunkFactoryTest : public ::testing::Test
{
  virtual void SetUp() override
  {
    Logger::get_instance().set_error_supression(true);
  }

  virtual void TearDown() override
  {
    Logger::get_instance().set_error_supression(false);
  }
};

TEST_F(DataChunkFactoryTest, should_create_data_chunk_when_exact)
{
  // Given
  const std::vector<BYTE> data(DataChunk::DATA_BYTE_SIZE);

  // When
  DataChunk chunk = ChunkFactory::get_chunk(data);

  // Then
  ASSERT_EQ(chunk.get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_create_data_chunk_when_less)
{
  // Given
  const std::vector<BYTE> data(
      GLOBAL::get_random_u64(1, DataChunk::DATA_BYTE_SIZE));

  // When
  DataChunk chunk = ChunkFactory::get_chunk(data);

  // Then
  ASSERT_EQ(chunk.get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_not_create_data_chunk_when_more)
{
  // Given
  const std::vector<BYTE> data(DataChunk::DATA_BYTE_SIZE + 1);

  // When
  bool thrownException = false;
  try
  {
    DataChunk chunk = ChunkFactory::get_chunk(data);
  }
  catch (const std::exception &e)
  {
    thrownException = true;
  }

  // Then
  ASSERT_TRUE(thrownException);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_exact)
{
  // Given
  const std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk chunk = ChunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_EQ(chunk.get_data(), data);
  ASSERT_EQ(chunk.get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_less)
{
  // Given
  const std::vector<BYTE> data(
      GLOBAL::get_random_u64(1, EncryptedDataChunk::DATA_BYTE_SIZE));
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk chunk = ChunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_EQ(chunk.get_data(), data);
  ASSERT_EQ(chunk.get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_more_vi)
{
  // Given
  const std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE + 1);

  // When
  bool thrownException = false;
  try
  {
    EncryptedDataChunk chunk =
        ChunkFactory::get_chunk(data, vi);
  }
  catch (const std::exception &e)
  {
    thrownException = true;
  }

  // Then
  ASSERT_TRUE(thrownException);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_more_data)
{
  // Given
  const std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE + 1);
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  bool thrownException = false;
  try
  {
    EncryptedDataChunk chunk =
        ChunkFactory::get_chunk(data, vi);
  }
  catch (const std::exception &e)
  {
    thrownException = true;
  }

  // Then
  ASSERT_TRUE(thrownException);
}

TEST_F(DataChunkFactoryTest, should_map_from_bytes_to_chunk_when_exact)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      DataChunk::DATA_BYTE_SIZE);

  // When
  DataChunk chunk = ChunkFactory::get_empty_chunk<DataChunk>();
  chunk.map_from_bytes(bytes);

  // Then
  ASSERT_EQ(bytes, chunk.get_data());
}

TEST_F(DataChunkFactoryTest, should_map_from_bytes_to_chunk_when_less)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      DataChunk::DATA_BYTE_SIZE -
      GLOBAL::get_random_u64(1, DataChunk::DATA_BYTE_SIZE));

  // When
  DataChunk chunk = ChunkFactory::get_empty_chunk<DataChunk>();
  chunk.map_from_bytes(bytes);

  // Then
  ASSERT_EQ(bytes, chunk.get_data());
}

TEST_F(DataChunkFactoryTest, should_not_map_from_bytes_to_chunk_when_more)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      DataChunk::DATA_BYTE_SIZE +
      GLOBAL::get_random_u64(1, DataChunk::DATA_BYTE_SIZE));

  // When
  DataChunk chunk = ChunkFactory::get_empty_chunk<DataChunk>();
  bool thrownException = false;

  try
  {
    chunk.map_from_bytes(bytes);
  }
  catch (const std::exception &e)
  {
    thrownException = true;
  }

  // Then
  ASSERT_TRUE(thrownException);
}

TEST_F(DataChunkFactoryTest, should_map_from_bytes_to_encrypted_chunk_when_exact)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      EncryptedDataChunk::DATA_BYTE_SIZE + EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk chunk =
      ChunkFactory::get_empty_chunk<EncryptedDataChunk>();
  chunk.map_from_bytes(bytes);

  std::vector<BYTE> vi(
      bytes.begin(), bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE);
  std::vector<BYTE> data(
      bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE, bytes.end());

  // Then
  ASSERT_EQ(data, chunk.get_data());
  ASSERT_EQ(vi, chunk.get_vi());
}

TEST_F(DataChunkFactoryTest, should_map_from_bytes_to_encrypted_chunk_when_less)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      GLOBAL::get_random_u64(1, EncryptedDataChunk::DATA_BYTE_SIZE) +
      EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk chunk =
      ChunkFactory::get_empty_chunk<EncryptedDataChunk>();
  chunk.map_from_bytes(bytes);

  std::vector<BYTE> data(
      bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE, bytes.end());
  std::vector<BYTE> vi(
      bytes.begin(), bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE);

  // Then
  ASSERT_EQ(data, chunk.get_data());
  ASSERT_EQ(vi, chunk.get_vi());
}

TEST_F(DataChunkFactoryTest, should_not_map_from_bytes_to_encrypted_chunk_when_less_than_vi)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      GLOBAL::get_random_u64(0, EncryptedDataChunk::VI_BYTE_SIZE - 1));

  // When
  EncryptedDataChunk chunk =
      ChunkFactory::get_empty_chunk<EncryptedDataChunk>();

  bool thrownException;
  try
  {
    chunk.map_from_bytes(bytes);
  }
  catch (const std::exception &e)
  {
    thrownException = true;
  }

  // Then
  ASSERT_TRUE(thrownException);
}

TEST_F(DataChunkFactoryTest, should_not_map_from_bytes_to_encrypted_chunk_when_more)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      EncryptedDataChunk::DATA_BYTE_SIZE + 1);

  // When
  EncryptedDataChunk chunk =
      ChunkFactory::get_empty_chunk<EncryptedDataChunk>();

  bool thrownException;
  try
  {
    chunk.map_from_bytes(bytes);
  }
  catch (const std::exception &e)
  {
    thrownException = true;
  }

  // Then
  ASSERT_TRUE(thrownException);
}