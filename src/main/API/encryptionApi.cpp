#include "encryptionApi.h"

const EncryptionApi::EncryptionFunction EncryptionApi::ENCRYPT_BIND =
    std::bind(&ChunkEncryption::encrypt_chunk,
              std::placeholders::_1, std::placeholders::_2);
const EncryptionApi::DecryptionFunction EncryptionApi::DECRYPT_BIND =
    std::bind(&ChunkEncryption::decrypt_chunk,
              std::placeholders::_1, std::placeholders::_2);

void EncryptionApi::encrypt_file(
    const std::filesystem::path &filePathSource,
    const std::filesystem::path &filePathDestination,
    const std::vector<BYTE> &key)
{
  THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

  if (!FileAccess::create_file(filePathDestination))
  {
    THROW_FILE_EXCEPTION("Unable to create file!", filePathDestination);
  }

  const u64 chunkCount = Batching::get_chunk_count_in_file(
      filePathSource, DataChunk::get_desired_chunk_size());
  for (u64 chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
  {
    process_and_append_chunk_to_file<DataChunk, EncryptedDataChunk>(
        ENCRYPT_BIND, filePathSource, filePathDestination, key, chunkIndex);
  }
}

void EncryptionApi::decrypt_file(
    const std::filesystem::path &filePathSource,
    const std::filesystem::path &filePathDestination,
    const std::vector<BYTE> &key)
{
  THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

  if (!FileAccess::create_file(filePathDestination))
  {
    THROW_FILE_EXCEPTION("Unable to create file!", filePathDestination);
  }

  const u64 chunkCount = Batching::get_chunk_count_in_file(
      filePathSource, EncryptedDataChunk::get_desired_chunk_size());
  for (u64 chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
  {
    process_and_append_chunk_to_file<EncryptedDataChunk, DataChunk>(
        DECRYPT_BIND, filePathSource, filePathDestination, key, chunkIndex);
  }
}