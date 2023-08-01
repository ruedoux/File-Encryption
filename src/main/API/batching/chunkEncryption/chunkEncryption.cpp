#include "chunkEncryption.h"

DataChunk ChunkEncryption::decrypt_chunk(
    const EncryptedDataChunk &encryptedChunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> data = encryptedChunk.get_data();
  const std::vector<BYTE> vi = encryptedChunk.get_vi();

  return ChunkFactory::get_chunk(Encryption::decrypt(data, key, vi));
}

EncryptedDataChunk ChunkEncryption::encrypt_chunk(
    const DataChunk &chunk,
    const std::vector<BYTE> &key)
{
  const std::vector<BYTE> data = chunk.get_data();
  const std::vector<BYTE> vi = Encryption::get_random_bytes(
      Encryption::VI_BYTE_SIZE);

  return ChunkFactory::get_chunk(Encryption::encrypt(data, key, vi), vi);
}