#include "encryptionInterface.h"

void EncryptionInterface::encrypt_file(
    const std::string &filePathSource,
    const std::string &filePathDestination,
    const std::vector<BYTE> &key)
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
    DataChunk chunk = Batching::read_chunk_from_file<DataChunk>(
        filePathSource, i, DataChunk::DATA_BYTE_SIZE);

    EncryptedDataChunk encryptedChunk = encrypt_chunk(chunk, key);

    Batching::append_chunk_to_file(filePathDestination, encryptedChunk);
  }
}

void EncryptionInterface::decrypt_file(
    const std::string &filePathSource,
    const std::string &filePathDestination,
    const std::vector<BYTE> &key)
{
  THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);
}

DataChunk EncryptionInterface::decrypt_chunk(
    const EncryptedDataChunk &encryptedChunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> &data = encryptedChunk.get_data();
  const std::vector<BYTE> &vi = encryptedChunk.get_vi();

  const DataChunk &decryptedChunk =
      ChunkFactory::get_chunk(Encryption::decrypt(data, key, vi));

  return decryptedChunk;
}

EncryptedDataChunk EncryptionInterface::encrypt_chunk(
    const DataChunk &chunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> &data = chunk.get_data();
  const std::vector<BYTE> &vi = Encryption::get_random_bytes(
      Encryption::KEY_BYTE_SIZE);

  EncryptedDataChunk encryptedChunk =
      ChunkFactory::get_chunk(Encryption::encrypt(data, key, vi), vi);

  return encryptedChunk;
}