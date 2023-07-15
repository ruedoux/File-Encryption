#include <gtest/gtest.h>
#include <encryption.h>
#include <global/utils/tools.h>

struct EncryptionIT : public ::testing::Test
{
  virtual void SetUp() override
  {
    srand(time(NULL));
  }
  virtual void TearDown() override {}
};

TEST_F(EncryptionIT, encrypt_bytes_and_decrypt_back)
{
  // Given
  std::vector<BYTE> bytes = Encryption::get_random_bytes(
      Tools::get_random_number(1024, 2056));
  std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_BYTE_SIZE);
  std::vector<BYTE> vi = Encryption::get_random_bytes(Encryption::VI_BYTE_SIZE);

  // When
  std::vector<BYTE> encryptedBytes = Encryption::encrypt(bytes, key, vi);
  std::vector<BYTE> decryptedBytes = Encryption::decrypt(encryptedBytes, key, vi);

  // Then
  ASSERT_EQ(bytes, decryptedBytes);
}
