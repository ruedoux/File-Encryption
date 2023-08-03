#include <gtest/gtest.h>
#include <Api/batching/chunkEncryption/chunkEncryption.h>

namespace
{
  void encrypt_a_chunk_test(u64 chunkSize)
  {
    // Given
    DataChunk chunk = ChunkFactory::get_chunk(
        Encryption::get_random_bytes(chunkSize));
    std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_BYTE_SIZE);

    // When
    EncryptedDataChunk encryptedChunk = ChunkEncryption::encrypt_chunk(chunk, key);

    // Then
    ASSERT_EQ(
        chunkSize + Encryption::VI_BYTE_SIZE,
        encryptedChunk.get_entire_chunk_size());
  }

  void decrypt_a_chunk_test(u64 chunkSize)
  {
    // Given
    EncryptedDataChunk chunk = ChunkFactory::get_chunk(
        Encryption::get_random_bytes(chunkSize),
        Encryption::get_random_bytes(Encryption::VI_BYTE_SIZE));
    std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_BYTE_SIZE);

    // When
    DataChunk decryptedChunk = ChunkEncryption::decrypt_chunk(chunk, key);

    // Then
    ASSERT_EQ(chunkSize, decryptedChunk.get_entire_chunk_size());
  }
}

struct ChunkEncryptionTest : public ::testing::Test
{
  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST_F(ChunkEncryptionTest, should_encrypt_exact_chunk)
{
  encrypt_a_chunk_test(DataChunk::get_desired_chunk_size());
}

TEST_F(ChunkEncryptionTest, should_encrypt_random_chunk)
{
  encrypt_a_chunk_test(
      Global::get_random_u64(1, DataChunk::get_desired_chunk_size() - 1));
}

TEST_F(ChunkEncryptionTest, should_decrypt_exact_chunk)
{
  decrypt_a_chunk_test(EncryptedDataChunk::DATA_BYTE_SIZE);
}

TEST_F(ChunkEncryptionTest, should_decrypt_random_chunk)
{
  decrypt_a_chunk_test(
      Global::get_random_u64(1, EncryptedDataChunk::DATA_BYTE_SIZE - 1));
}