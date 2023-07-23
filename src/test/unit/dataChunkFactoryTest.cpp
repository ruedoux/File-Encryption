#include <gtest/gtest.h>
#include <batching/dataChunk/dataChunkFactory.h>

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
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(data);

  // Then
  ASSERT_NE(dataChunk, DataChunk::ErrorDataChunk);
}

TEST_F(DataChunkFactoryTest, should_create_data_chunk_when_less)
{
  // Given
  std::vector<BYTE> data(RANDOM_NUMBER(1, DataChunk::DATA_BYTE_SIZE));

  // When
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(data);

  // Then
  ASSERT_NE(dataChunk, DataChunk::ErrorDataChunk);
}

TEST_F(DataChunkFactoryTest, should_not_create_data_chunk_when_incorrect)
{
  // Given
  std::vector<BYTE> data(DataChunk::DATA_BYTE_SIZE + 123);

  // When
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(data);

  // Then
  ASSERT_EQ(dataChunk, DataChunk::ErrorDataChunk);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_exact)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // Then
  ASSERT_NE(encryptedDataChunk, EncryptedDataChunk::ErrorEncryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_less)
{
  // Given
  std::vector<BYTE> data(RANDOM_NUMBER(1, EncryptedDataChunk::DATA_BYTE_SIZE));
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // Then
  ASSERT_NE(encryptedDataChunk, EncryptedDataChunk::ErrorEncryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect_vi)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE + 123);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // Then
  ASSERT_EQ(encryptedDataChunk, EncryptedDataChunk::ErrorEncryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect_data)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE + 123);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // Then
  ASSERT_EQ(encryptedDataChunk, EncryptedDataChunk::ErrorEncryptedDataChunk);
}