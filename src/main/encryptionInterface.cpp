#include "encryptionInterface.h"

const EncryptionInterface::EncryptionFunction EncryptionInterface::ENCRYPT_BIND =
    std::bind(&EncryptionInterface::encrypt_chunk,
              std::placeholders::_1, std::placeholders::_2);
const EncryptionInterface::DecryptionFunction EncryptionInterface::DECRYPT_BIND =
    std::bind(&EncryptionInterface::decrypt_chunk,
              std::placeholders::_1, std::placeholders::_2);

DataChunk EncryptionInterface::decrypt_chunk(
    const EncryptedDataChunk &encryptedChunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> data = encryptedChunk.get_data();
  const std::vector<BYTE> vi = encryptedChunk.get_vi();

  return ChunkFactory::get_chunk(Encryption::decrypt(data, key, vi));
}

EncryptedDataChunk EncryptionInterface::encrypt_chunk(
    const DataChunk &chunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> data = chunk.get_data();
  const std::vector<BYTE> vi = Encryption::get_random_bytes(
      Encryption::VI_BYTE_SIZE);

  return ChunkFactory::get_chunk(Encryption::encrypt(data, key, vi), vi);
}

std::uintmax_t EncryptionInterface::get_bytes_left_in_last_chunk(
    const std::string &filePath,
    const u64 chunkSize)
{
  const std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
  std::uintmax_t bytesLeft = fileSize % chunkSize;
  if ((fileSize > 0) && (bytesLeft == 0))
  {
    bytesLeft = chunkSize;
  }
  return bytesLeft;
}