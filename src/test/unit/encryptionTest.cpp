#include <gtest/gtest.h>
#include <batching/chunkEncryption/dataChunk/encryption/encryption.h>

struct EncryptionTest : public ::testing::Test
{
  virtual void SetUp() override
  {
  }
  virtual void TearDown() override {}
};

TEST_F(EncryptionTest, encrypt_bytes_and_decrypt_back)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(GLOBAL::get_random_number(1024, 2056));
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
  std::vector<BYTE> bytes = Encryption::get_random_bytes(GLOBAL::get_random_number(2, 12));
  std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_BYTE_SIZE);
  std::vector<BYTE> vi = Encryption::get_random_bytes(Encryption::VI_BYTE_SIZE);

  // When
  std::vector<BYTE> encryptedBytes = Encryption::encrypt(bytes, key, vi);
  std::vector<BYTE> decryptedBytes = Encryption::decrypt(encryptedBytes, key, vi);

  // Then
  ASSERT_EQ(bytes, decryptedBytes);
}
