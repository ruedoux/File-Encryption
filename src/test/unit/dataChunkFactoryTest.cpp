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
  std::vector<BYTE> data(DataChunk::DATA_BYTE_SIZE);

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_create_data_chunk_when_less)
{
  // Given
  std::vector<BYTE> data(RANDOM_NUMBER(1, DataChunk::DATA_BYTE_SIZE));

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_not_create_data_chunk_when_incorrect)
{
  // Given
  std::vector<BYTE> data(DataChunk::DATA_BYTE_SIZE + 123);

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(chunkContainer.get_result().get_data(), data);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_exact)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
  ASSERT_EQ(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_less)
{
  // Given
  std::vector<BYTE> data(RANDOM_NUMBER(1, EncryptedDataChunk::DATA_BYTE_SIZE));
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(!chunkContainer.is_error());
  ASSERT_EQ(chunkContainer.get_result().get_data(), data);
  ASSERT_EQ(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect_vi)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE + 123);

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(chunkContainer.get_result().get_data(), data);
  ASSERT_NE(chunkContainer.get_result().get_vi(), vi);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect_data)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE + 123);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  ChunkContainer chunkContainer = chunkFactory::get_chunk(data, vi);

  // Then
  ASSERT_TRUE(chunkContainer.is_error());
  ASSERT_NE(chunkContainer.get_result().get_data(), data);
  ASSERT_NE(chunkContainer.get_result().get_vi(), vi);
}