#include <gtest/gtest.h>
#include <Api/batching/chunkEncryption/chunkEncryption.h>

namespace
{
  void encrypt_and_decrypt_a_chunk_test(u64 chunkSize)
  {
    // Given
    DataChunk chunk = ChunkFactory::get_chunk(
        Encryption::get_random_bytes(chunkSize));
    std::vector<BYTE> key = Encryption::get_random_bytes(
        Global::get_random_u64(4, Encryption::KEY_BYTE_SIZE));

    // When
    EncryptedDataChunk encryptedChunk = ChunkEncryption::encrypt_chunk(chunk, key);
    DataChunk decryptedChunk = ChunkEncryption::decrypt_chunk(encryptedChunk, key);

    // Then
    ASSERT_EQ(chunk, decryptedChunk);
  }
}

struct ChunkEncryptionIT : public ::testing::Test
{
  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST_F(ChunkEncryptionIT, should_encrypt_and_decrypt_exact_chunk)
{
  encrypt_and_decrypt_a_chunk_test(DataChunk::DATA_BYTE_SIZE);
}

TEST_F(ChunkEncryptionIT, should_encrypt_and_decrypt_random_chunk)
{
  encrypt_and_decrypt_a_chunk_test(
      Global::get_random_u64(1, DataChunk::DATA_BYTE_SIZE - 1));
}