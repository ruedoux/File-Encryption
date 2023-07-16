#include <gtest/gtest.h>
#include <batching/dataChunkFactory.h>

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

TEST_F(DataChunkFactoryTest, should_create_data_chunk_when_correct)
{
  // Given
  std::vector<BYTE> data(DataChunk::CHUNK_BYTE_SIZE);

  // When
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(data);

  // Then
  ASSERT_NE(dataChunk, DataChunk::ErrorDataChunk);
}

TEST_F(DataChunkFactoryTest, should_not_create_data_chunk_when_incorrect)
{
  // Given
  std::vector<BYTE> data(123);

  // When
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(data);

  // Then
  ASSERT_EQ(dataChunk, DataChunk::ErrorDataChunk);
}

TEST_F(DataChunkFactoryTest, should_create_encrypted_chunk_when_correct)
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

TEST_F(DataChunkFactoryTest, should_not_create_encrypted_chunk_when_incorrect)
{
  // Given
  std::vector<BYTE> data(123);
  std::vector<BYTE> vi(321);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // Then
  ASSERT_EQ(encryptedDataChunk, EncryptedDataChunk::ErrorEncryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_map_from_encrypted_to_data_chunk)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // When
  DataChunk dataChunk =
      DataChunkFactory::map_EncryptedDataChunk_to_DataChunk(
          encryptedDataChunk);

  // Then
  ASSERT_EQ(encryptedDataChunk, dataChunk);
}

TEST_F(DataChunkFactoryTest, should_map_from_data_chunk_to_encrypted)
{
  Logger::get_instance().set_error_supression(false);

  // Given
  std::vector<BYTE> data(DataChunk::CHUNK_BYTE_SIZE);
  DataChunk dataChunk =
      DataChunkFactory::get_DataChunk(data);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::map_DataChunk_to_EncryptedDataChunk(
          dataChunk);

  // Then
  ASSERT_EQ(dataChunk, encryptedDataChunk);
}