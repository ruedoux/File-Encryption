#include <gtest/gtest.h>
#include <batching/dataChunk/chunkFactory.h>

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
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_create_data_chunk_when_less)
{
  // Given
  const std::vector<BYTE> data(RANDOM_NUMBER(1, DataChunk::DATA_BYTE_SIZE));

  // When
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_not_create_data_chunk_when_incorrect)
{
  // Given
  const std::vector<BYTE> data(DataChunk::DATA_BYTE_SIZE + 123);

  // When
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(chunkContainer.get_result().get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_exact)
{
  // Given
  const std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
  ASSERT_EQ(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_less)
{
  // Given
  const std::vector<BYTE> data(RANDOM_NUMBER(1, EncryptedDataChunk::DATA_BYTE_SIZE));
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
  ASSERT_EQ(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect_vi)
{
  // Given
  const std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE + 123);

  // When
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(chunkContainer.get_result().get_data(), data);
  ASSERT_NE(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect_data)
{
  // Given
  const std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE + 123);
  const std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  const ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(chunkContainer.get_result().get_data(), data);
  ASSERT_NE(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_map_exact_bytes_to_encrypted_chunk)
{
  Logger::get_instance().set_error_supression(false);
  // Given
  const std::vector<BYTE> bytes = Encryption::get_random_bytes(
      EncryptedDataChunk::DATA_BYTE_SIZE + EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  const ChunkContainer chunkContainer =
      chunkFactory::map_bytes_to_encrypted_chunk(bytes);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(bytes, chunkContainer.get_result().get_entire_chunk());
  Logger::get_instance().set_error_supression(true);
}

TEST_F(DataChunkFactoryTest, should_map_less_with_vi_bytes_to_encrypted_chunk)
{
  // Given
  const std::vector<BYTE> bytes = Encryption::get_random_bytes(
      EncryptedDataChunk::VI_BYTE_SIZE + RANDOM_NUMBER(0, EncryptedDataChunk::DATA_BYTE_SIZE - 1));

  // When
  const ChunkContainer chunkContainer =
      chunkFactory::map_bytes_to_encrypted_chunk(bytes);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(bytes, chunkContainer.get_result().get_entire_chunk());
}

TEST_F(DataChunkFactoryTest, should_not_map_less_without_vi_bytes_to_encrypted_chunk)
{
  // Given
  const std::vector<BYTE> bytes = Encryption::get_random_bytes(
      RANDOM_NUMBER(0, EncryptedDataChunk::VI_BYTE_SIZE - 1));

  // When
  const ChunkContainer chunkContainer =
      chunkFactory::map_bytes_to_encrypted_chunk(bytes);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(bytes, chunkContainer.get_result().get_entire_chunk());
}

TEST_F(DataChunkFactoryTest, should_not_map_more_bytes_to_encrypted_chunk)
{
  // Given
  const std::vector<BYTE> bytes = Encryption::get_random_bytes(
      EncryptedDataChunk::DATA_BYTE_SIZE + EncryptedDataChunk::VI_BYTE_SIZE + 1);

  // When
  const ChunkContainer chunkContainer =
      chunkFactory::map_bytes_to_encrypted_chunk(bytes);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(bytes, chunkContainer.get_result().get_entire_chunk());
}