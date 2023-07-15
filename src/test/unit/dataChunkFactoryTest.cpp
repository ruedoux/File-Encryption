#include <gtest/gtest.h>
#include <batching/dataChunkFactory.h>

struct DataChunkFactoryTest : public ::testing::Test
{
  virtual void SetUp() override
  {
  }

  virtual void TearDown() override
  {
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