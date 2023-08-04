#include <gtest/gtest.h>
#include <Api/encryptionApi.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
  const std::string TEST_FILE_SOURCE_NAME = "FileSrc";
  const std::string TEST_FILE_ENCRYPTED_NAME = "FileEncrypted";
  const std::string TEST_FILE_DECRYPTED_NAME = "FileDecrypted";
  const std::string TEST_FILE_PATH_SOURCE = TEST_FOLDER + "/" + TEST_FILE_SOURCE_NAME;
  const std::string TEST_FILE_PATH_ENCRYPTED = TEST_FOLDER + "/" + TEST_FILE_ENCRYPTED_NAME;
  const std::string TEST_FILE_PATH_DECRYPTED = TEST_FOLDER + "/" + TEST_FILE_DECRYPTED_NAME;

  void encrypt_and_decrypt_a_file_test(
      const u64 exactChunkCount,
      const bool randomBytes)
  {
    // Given
    const u64 chunkSize = DataChunk::get_desired_chunk_size();

    u64 fileSizeDeclared = chunkSize * exactChunkCount;
    if (randomBytes)
    {
      fileSizeDeclared += Global::get_random_u64(1, chunkSize - 1);
    }

    Logger::log_info("File size declared: " + std::to_string(fileSizeDeclared));

    const std::vector<BYTE> bytesInFile =
        Encryption::get_random_bytes(fileSizeDeclared);
    const std::vector<BYTE> randomKey = Encryption::get_random_bytes(
        Global::get_random_u64(4, Encryption::KEY_BYTE_SIZE));
    
    Logger::log_info("Random key size: " + std::to_string(randomKey.size()));

    // When
    bool createdFile = FileAccess::create_file(TEST_FILE_PATH_SOURCE);
    FileAccess::ErrorCode appendedToFile = FileAccess::append_bytes_to_file(
        TEST_FILE_PATH_SOURCE, bytesInFile);

    EncryptionApi::encrypt_file(
        TEST_FILE_PATH_SOURCE,
        TEST_FILE_PATH_ENCRYPTED,
        randomKey);

    EncryptionApi::decrypt_file(
        TEST_FILE_PATH_ENCRYPTED,
        TEST_FILE_PATH_DECRYPTED,
        randomKey);

    std::uintmax_t decryptedFileSize = FileAccess::get_file_size(TEST_FILE_PATH_DECRYPTED);
    std::vector<BYTE> decryptedFileBytes;
    FileAccess::ErrorCode readFromFile = FileAccess::read_bytes_from_file(
        TEST_FILE_PATH_DECRYPTED, decryptedFileBytes, 0, bytesInFile.size());

    // Then
    ASSERT_TRUE(createdFile);
    ASSERT_EQ(FileAccess::ErrorCode::OK, appendedToFile);
    ASSERT_EQ(FileAccess::ErrorCode::OK, readFromFile);
    ASSERT_EQ(fileSizeDeclared, decryptedFileSize);
    ASSERT_EQ(bytesInFile, decryptedFileBytes);
  }
}

struct EncryptionApiIT : public ::testing::Test
{
  virtual void SetUp() override
  {
    std::filesystem::create_directory(TEST_FOLDER);
  }

  virtual void TearDown() override
  {
    std::filesystem::remove_all(TEST_FOLDER);
  }
};

TEST_F(EncryptionApiIT, encrypts_and_decrypts_a_file_with_random_less_than_one)
{
  encrypt_and_decrypt_a_file_test(0, true);
}

TEST_F(EncryptionApiIT, encrypts_and_decrypts_a_file_with_single_exact_chunk)
{
  encrypt_and_decrypt_a_file_test(1, false);
}

TEST_F(EncryptionApiIT, encrypts_and_decrypts_a_file_with_multiple_exact_chunks)
{
  encrypt_and_decrypt_a_file_test(Global::get_random_u64(2, 6), false);
}

TEST_F(EncryptionApiIT, encrypts_and_decrypts_a_file_with_single_random_chunk)
{
  encrypt_and_decrypt_a_file_test(1, true);
}

TEST_F(EncryptionApiIT, encrypts_and_decrypts_a_file_with_multiple_random_chunks)
{
  // encrypt_and_decrypt_a_file_test(Global::get_random_u64(2, 6), true);
}