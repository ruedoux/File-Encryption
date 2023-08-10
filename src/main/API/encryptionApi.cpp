#include "encryptionApi.h"

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

  const u64 chunkSizeFrom = DataChunk::get_desired_chunk_size();
  const uintmax_t fileSize = FileAccess::get_file_size(filePathSource);

  THROW_EXCEPTION_IF_TRUE(fileSize == 0);

  const u64 chunkCount = Batching::get_chunk_count_in_file(
      filePathSource, DataChunk::get_desired_chunk_size());
  for (u64 chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
  {
    const uintmax_t lastByteIndex = chunkSizeFrom * chunkIndex + chunkSizeFrom;

    const u64 bytesToRead =
        (lastByteIndex < fileSize) ? chunkSizeFrom : chunkSizeFrom - (lastByteIndex - fileSize);

    const DataChunk chunk = Batching::read_chunk_from_file<DataChunk>(
        filePathSource, chunkIndex, bytesToRead);

    Batching::append_chunk_to_file(
        filePathDestination, ChunkEncryption::encrypt_chunk(chunk, key));
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

  const u64 chunkSizeFrom = EncryptedDataChunk::get_desired_chunk_size();
  const uintmax_t fileSize = FileAccess::get_file_size(filePathSource);

  THROW_EXCEPTION_IF_TRUE(fileSize == 0);

  const u64 chunkCount = Batching::get_chunk_count_in_file(
      filePathSource, EncryptedDataChunk::get_desired_chunk_size());
  for (u64 chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
  {
    const uintmax_t lastByteIndex = chunkSizeFrom * chunkIndex + chunkSizeFrom;

    const u64 bytesToRead =
        (lastByteIndex < fileSize) ? chunkSizeFrom : chunkSizeFrom - (lastByteIndex - fileSize);

    const EncryptedDataChunk chunk = Batching::read_chunk_from_file<EncryptedDataChunk>(
        filePathSource, chunkIndex, bytesToRead);

    Batching::append_chunk_to_file(
        filePathDestination, ChunkEncryption::decrypt_chunk(chunk, key));
  }
}