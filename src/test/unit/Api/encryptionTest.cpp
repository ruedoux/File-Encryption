#include <gtest/gtest.h>
#include <Api/batching/chunkEncryption/dataChunk/encryption/encryption.h>
#include <Api/global/logger.h>

struct EncryptionTest : public ::testing::Test
{
  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST_F(EncryptionTest, encrypt_bytes_and_decrypt_back)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(Global::get_random_u64(1024, 2056));
  std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_BYTE_SIZE);
  std::vector<BYTE> vi = Encryption::get_random_bytes(Encryption::VI_BYTE_SIZE);

  // When
  std::vector<BYTE> encryptedBytes = Encryption::encrypt(bytes, key, vi);
  std::vector<BYTE> decryptedBytes = Encryption::decrypt(encryptedBytes, key, vi);

  // Then
  ASSERT_EQ(bytes, decryptedBytes);
}

TEST_F(EncryptionTest, encrypt_bytes_and_decrypt_back_small)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(Global::get_random_u64(2, 12));
  std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_BYTE_SIZE);
  std::vector<BYTE> vi = Encryption::get_random_bytes(Encryption::VI_BYTE_SIZE);

  // When
  std::vector<BYTE> encryptedBytes = Encryption::encrypt(bytes, key, vi);
  std::vector<BYTE> decryptedBytes = Encryption::decrypt(encryptedBytes, key, vi);

  // Then
  ASSERT_EQ(bytes, decryptedBytes);
}

TEST_F(EncryptionTest, encrypt_bytes_and_decrypt_random_key_rotate)
{
  for (u64 keySize = 1; keySize < Encryption::KEY_BYTE_SIZE + 1; keySize++)
  {
    Logger::log("keySize: " + std::to_string(keySize));

    // Given
    std::vector<BYTE> bytes = Encryption::get_random_bytes(
        Global::get_random_u64(1024, 2056));
    std::vector<BYTE> key = Encryption::get_random_bytes(keySize);
    std::vector<BYTE> vi = Encryption::get_random_bytes(Encryption::VI_BYTE_SIZE);

    // When
    std::vector<BYTE> encryptedBytes = Encryption::encrypt(bytes, key, vi);
    std::vector<BYTE> decryptedBytes = Encryption::decrypt(encryptedBytes, key, vi);

    // Then
    ASSERT_EQ(bytes, decryptedBytes);
  }
}

TEST_F(EncryptionTest, pad_bytes_rotate)
{
  for (u64 size = 1; size < Encryption::KEY_BYTE_SIZE + 1; size++)
  {
    Logger::log("Size: " + std::to_string(size));

    // Given
    std::vector<BYTE> bytes = Encryption::get_random_bytes(size);

    // When
    std::vector<BYTE> paddedBytes = Encryption::get_padded_bytes(
        bytes, Encryption::KEY_BYTE_SIZE);

    // Then
    ASSERT_EQ(Encryption::KEY_BYTE_SIZE, paddedBytes.size());
    for (u64 i = 0; i < paddedBytes.size(); i++)
    {
      if (i < bytes.size())
      {
        ASSERT_EQ(bytes[i], paddedBytes[i]);
      }
      else
      {
        ASSERT_EQ(0, paddedBytes[i]);
      }
    }
  }
}

TEST_F(EncryptionTest, hash_bytes_rotate)
{
  for (u64 size = 1; size < Encryption::KEY_BYTE_SIZE + 1; size++)
  {
    Logger::log("Size: " + std::to_string(size));

    // Given
    std::vector<BYTE> bytes = Encryption::get_random_bytes(size);

    // When
    std::vector<BYTE> hashedBytes = Encryption::get_hashed_key(bytes);

    // Then
    ASSERT_EQ(Encryption::KEY_BYTE_SIZE, hashedBytes.size());
    ASSERT_EQ(hashedBytes, Encryption::get_hashed_key(bytes));
  }
}

TEST_F(EncryptionTest, stretch_bytes_rotate)
{
  for (u64 size = 1; size < Encryption::KEY_BYTE_SIZE + 1; size++)
  {
    Logger::log("Size: " + std::to_string(size));
    
    // Given
    std::vector<BYTE> bytes = Encryption::get_random_bytes(size);

    // When
    std::vector<BYTE> hashedBytes = Encryption::get_stretched_key(bytes);

    // Then
    ASSERT_EQ(Encryption::KEY_BYTE_SIZE, hashedBytes.size());
    ASSERT_EQ(hashedBytes, Encryption::get_stretched_key(bytes));
  }
}