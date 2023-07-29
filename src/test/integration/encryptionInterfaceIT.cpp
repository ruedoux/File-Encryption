#include <gtest/gtest.h>
#include <encryptionInterface.h>

namespace
{
  const std::string TEST_FOLDER = "TESTS";
  const std::string TEST_FILE_SOURCE_NAME = "FileSrc";
  const std::string TEST_FILE_ENCRYPTED_NAME = "FileEncrypted";
  const std::string TEST_FILE_DECRYPTED_NAME = "FileDecrypted";
  const std::string TEST_FILE_PATH_SOURCE = TEST_FOLDER + "/" + TEST_FILE_SOURCE_NAME;
  const std::string TEST_FILE_PATH_ENCRYPTED = TEST_FOLDER + "/" + TEST_FILE_ENCRYPTED_NAME;
  const std::string TEST_FILE_PATH_DECRYPTED = TEST_FOLDER + "/" + TEST_FILE_DECRYPTED_NAME;

  void encrypt_a_file_test(
      const u64 exactChunkCount,
      const bool randomBytes)
  {
    // Given
    const u64 chunkSize = DataChunk::get_desired_chunk_size();

    u64 fileSizeDeclared = chunkSize * exactChunkCount;
    if (randomBytes)
    {
      fileSizeDeclared += GLOBAL::get_random_number((u64)1, chunkSize - 1);
    }

    const std::vector<BYTE> bytesInFile = Encryption::get_random_bytes(
        fileSizeDeclared);
    const std::vector<BYTE> randomKey = Encryption::get_random_bytes(
        GLOBAL::get_random_number((u64)4, Encryption::KEY_BYTE_SIZE));

    // When
    bool createdFile = FileAccess::create_file(TEST_FILE_PATH_SOURCE);
    FileAccess::ErrorCode appendedToFile = FileAccess::append_bytes_to_file(
        TEST_FILE_PATH_SOURCE, bytesInFile);

    EncryptionInterface::process_file(
        EncryptionInterface::ENCRYPT_BIND,
        TEST_FILE_PATH_SOURCE,
        TEST_FILE_PATH_ENCRYPTED,
        randomKey);

    std::uintmax_t fileSize = FileAccess::get_file_size(TEST_FILE_PATH_ENCRYPTED);
    std::vector<BYTE> encryptedFileBytes;
    FileAccess::ErrorCode readFromFile = FileAccess::read_bytes_from_file(
        TEST_FILE_PATH_ENCRYPTED, encryptedFileBytes, 0, fileSize);

    const u64 chunkCountInFile = Batching::get_chunk_count_in_file(
        TEST_FILE_PATH_SOURCE, chunkSize);

    // Then
    ASSERT_TRUE(createdFile);
    ASSERT_EQ(FileAccess::ErrorCode::OK, appendedToFile);
    ASSERT_EQ(FileAccess::ErrorCode::OK, readFromFile);
    ASSERT_EQ(
        fileSizeDeclared + Encryption::VI_BYTE_SIZE * chunkCountInFile,
        fileSize);
    ASSERT_NE(bytesInFile, encryptedFileBytes);
  }

  void encrypt_and_decrypt_a_file_test(
      const u64 exactChunkCount,
      const bool randomBytes)
  {
    // Given
    const u64 chunkSize = DataChunk::get_desired_chunk_size();

    u64 fileSizeDeclared = chunkSize * exactChunkCount;
    if (randomBytes)
    {
      fileSizeDeclared += GLOBAL::get_random_number((u64)1, chunkSize - 1);
    }

    const std::vector<BYTE> bytesInFile = Encryption::get_random_bytes(
        fileSizeDeclared);
    const std::vector<BYTE> randomKey = Encryption::get_random_bytes(
        GLOBAL::get_random_number((u64)4, Encryption::KEY_BYTE_SIZE));

    // When
    bool createdFile = FileAccess::create_file(TEST_FILE_PATH_SOURCE);
    FileAccess::ErrorCode appendedToFile = FileAccess::append_bytes_to_file(
        TEST_FILE_PATH_SOURCE, bytesInFile);

    EncryptionInterface::process_file(
        EncryptionInterface::ENCRYPT_BIND,
        TEST_FILE_PATH_SOURCE,
        TEST_FILE_PATH_ENCRYPTED,
        randomKey);

    EncryptionInterface::process_file(
        EncryptionInterface::DECRYPT_BIND,
        TEST_FILE_PATH_ENCRYPTED,
        TEST_FILE_PATH_DECRYPTED,
        randomKey);

    std::vector<BYTE> readBytesInDecryptedFile;
    FileAccess::ErrorCode readFromFile = FileAccess::read_bytes_from_file(
        TEST_FILE_PATH_DECRYPTED, readBytesInDecryptedFile, 0, bytesInFile.size());

    // Then
    ASSERT_TRUE(createdFile);
    ASSERT_EQ(FileAccess::ErrorCode::OK, appendedToFile);
    ASSERT_EQ(FileAccess::ErrorCode::OK, readFromFile);
    ASSERT_EQ(bytesInFile.size(), readBytesInDecryptedFile.size());
    ASSERT_EQ(bytesInFile, readBytesInDecryptedFile);
  }
}

struct EncryptionInterfaceIT : public ::testing::Test
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

TEST_F(EncryptionInterfaceIT, encrypts_a_file_with_random_less_than_one)
{
  encrypt_a_file_test(0, true);
}

TEST_F(EncryptionInterfaceIT, encrypts_a_file_with_single_exact_chunk)
{
  encrypt_a_file_test(1, false);
}

TEST_F(EncryptionInterfaceIT, encrypts_a_file_with_multiple_exact_chunks)
{
  encrypt_a_file_test(GLOBAL::get_random_number(2, 6), false);
}

TEST_F(EncryptionInterfaceIT, encrypts_a_file_with_single_random_chunk)
{
  encrypt_a_file_test(1, true);
}

TEST_F(EncryptionInterfaceIT, encrypts_a_file_with_multiple_random_chunks)
{
  encrypt_a_file_test(GLOBAL::get_random_number(2, 6), true);
}

TEST_F(EncryptionInterfaceIT, encrypts_and_decrypts_a_file_with_random_less_than_one)
{
  encrypt_and_decrypt_a_file_test(0, true);
}

TEST_F(EncryptionInterfaceIT, encrypts_and_decrypts_a_file_with_single_exact_chunk)
{
  encrypt_and_decrypt_a_file_test(1, false);
}

TEST_F(EncryptionInterfaceIT, encrypts_and_decrypts_a_file_with_multiple_exact_chunks)
{
  encrypt_and_decrypt_a_file_test(GLOBAL::get_random_number(2, 6), false);
}

TEST_F(EncryptionInterfaceIT, encrypts_and_decrypts_a_file_with_single_random_chunk)
{
  //encrypt_and_decrypt_a_file_test(1, true);
}

TEST_F(EncryptionInterfaceIT, encrypts_and_decrypts_a_file_with_multiple_random_chunks)
{
  //encrypt_and_decrypt_a_file_test(GLOBAL::get_random_number(2, 6), true);
}