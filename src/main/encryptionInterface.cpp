#include "encryptionInterface.h"

const EncryptionInterface::EncryptionFunction EncryptionInterface::ENCRYPT_BIND =
      std::bind(&EncryptionInterface::encrypt_chunk,
                std::placeholders::_1, std::placeholders::_2);
const EncryptionInterface::DecryptionFunction EncryptionInterface::DECRYPT_BIND =
      std::bind(&EncryptionInterface::encrypt_chunk,
                std::placeholders::_1, std::placeholders::_2);

DataChunk EncryptionInterface::decrypt_chunk(
    const EncryptedDataChunk &encryptedChunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> data = encryptedChunk.get_data();
  const std::vector<BYTE> vi = encryptedChunk.get_vi();

  const DataChunk decryptedChunk =
      ChunkFactory::get_chunk(Encryption::decrypt(data, key, vi));

  return decryptedChunk;
}

EncryptedDataChunk EncryptionInterface::encrypt_chunk(
    const DataChunk &chunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> data = chunk.get_data();
  const std::vector<BYTE> vi = Encryption::get_random_bytes(
      Encryption::VI_BYTE_SIZE);

  EncryptedDataChunk encryptedChunk =
      ChunkFactory::get_chunk(Encryption::encrypt(data, key, vi), vi);

  return encryptedChunk;
}