#include <gtest/gtest.h>
#include <batching/dataChunkFactory.h>
#include <global/utils/tools.h>

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

TEST_F(DataChunkFactoryTest, should_create_decrypted_chunk_when_correct)
{
  // Given
  std::vector<BYTE> data(DataChunk::CHUNK_BYTE_SIZE);

  // When
  DecryptedDataChunk decryptedDataChunk =
      DataChunkFactory::get_DecryptedDataChunk(data);

  // Then
  ASSERT_NE(decryptedDataChunk, DataChunkFactory::ErrorDecryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_not_create_decrypted_chunk_when_incorrect)
{
  // Given
  std::vector<BYTE> data(123);

  // When
  DecryptedDataChunk decryptedDataChunk =
      DataChunkFactory::get_DecryptedDataChunk(data);

  // Then
  ASSERT_EQ(decryptedDataChunk, DataChunkFactory::ErrorDecryptedDataChunk);
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
  ASSERT_NE(encryptedDataChunk, DataChunkFactory::ErrorEncryptedDataChunk);
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
  ASSERT_EQ(encryptedDataChunk, DataChunkFactory::ErrorEncryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_map_from_encrypted_to_decrypted)
{
  // Given
  std::vector<BYTE> data(EncryptedDataChunk::DATA_BYTE_SIZE);
  std::vector<BYTE> vi(EncryptedDataChunk::VI_BYTE_SIZE);
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::get_EncryptedDataChunk(data, vi);

  // When
  DecryptedDataChunk decryptedDataChunk =
      DataChunkFactory::map_EncryptedDataChunk_to_DecryptedDataChunk(
          encryptedDataChunk);

  // Then
  ASSERT_EQ(encryptedDataChunk, decryptedDataChunk);
}

TEST_F(DataChunkFactoryTest, should_map_from_decrypted_to_encrypted)
{
  Logger::get_instance().set_error_supression(false);

  // Given
  std::vector<BYTE> data(DataChunk::CHUNK_BYTE_SIZE);
  DecryptedDataChunk decryptedDataChunk =
      DataChunkFactory::get_DecryptedDataChunk(data);

  // When
  EncryptedDataChunk encryptedDataChunk =
      DataChunkFactory::map_DecryptedDataChunk_to_EncryptedDataChunk(
          decryptedDataChunk);

  // Then
  ASSERT_EQ(decryptedDataChunk, encryptedDataChunk);
}