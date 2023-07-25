#include "encryptionInterface.h"

bool EncryptionInterface::encrypt_file(
    const std::string &filePathSource,
    const std::string &filePathDestination,
    const std::vector<BYTE> key)
{
  THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

  const u64 chunkCount = Batching::get_chunk_count_in_file(
      filePathSource, DataChunk::DATA_BYTE_SIZE);
  const u64 lastChunkIndex = chunkCount * DataChunk::DATA_BYTE_SIZE;
  const std::uintmax_t bytesLeftInLastChunk =
      FileAccess::get_byte_count_left_in_file(filePathSource, lastChunkIndex);

  if (!FileAccess::create_file(filePathDestination))
  {
    THROW_FILE_EXCEPTION("Unable to create file!", filePathDestination);
  }

  for (u64 i = 0; i < chunkCount - 1; i++) // -1 because excluding last chunk
  {
    const u64 fromIndex = DataChunk::DATA_BYTE_SIZE * i;

    
  }

  return true;
}

bool EncryptionInterface::decrypt_file(
    const std::string &filePathSource,
    const std::string &filePathDestination,
    const std::vector<BYTE> key)
{
  THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

  return true;
}