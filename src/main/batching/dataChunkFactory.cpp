#include "dataChunkFactory.h"

const DecryptedDataChunk DataChunkFactory::ErrorDecryptedDataChunk =
    DecryptedDataChunk(std::vector<BYTE>());
const EncryptedDataChunk DataChunkFactory::ErrorEncryptedDataChunk =
    EncryptedDataChunk(std::vector<BYTE>(), std::vector<BYTE>());

DecryptedDataChunk DataChunkFactory::get_DecryptedDataChunk(
    std::vector<BYTE> &data)
{
  LOGGER_RETURN_IF_NOT_MATCH(
      data.size(),
      DecryptedDataChunk::CHUNK_BYTE_SIZE,
      ErrorDecryptedDataChunk)
  return DecryptedDataChunk(data);
}

EncryptedDataChunk DataChunkFactory::get_EncryptedDataChunk(
    std::vector<BYTE> &data,
    std::vector<BYTE> &vi)
{
  LOGGER_RETURN_IF_NOT_MATCH(
      data.size(),
      EncryptedDataChunk::DATA_BYTE_SIZE,
      ErrorEncryptedDataChunk)
  LOGGER_RETURN_IF_NOT_MATCH(
      vi.size(),
      EncryptedDataChunk::VI_BYTE_SIZE,
      ErrorEncryptedDataChunk)
  return EncryptedDataChunk(data, vi);
}

DecryptedDataChunk DataChunkFactory::map_EncryptedDataChunk_to_DecryptedDataChunk(
    const EncryptedDataChunk &encryptedDataChunk)
{
  return DecryptedDataChunk(encryptedDataChunk.get_entire_chunk());
}

EncryptedDataChunk DataChunkFactory::map_DecryptedDataChunk_to_EncryptedDataChunk(
    const DecryptedDataChunk &decryptedDataChunk)
{
  const std::vector<BYTE> &entireChunk = decryptedDataChunk.get_entire_chunk();

  std::vector<BYTE> vi(
      entireChunk.begin(),
      entireChunk.begin() + EncryptedDataChunk::VI_BYTE_SIZE);
  std::vector<BYTE> data(
      entireChunk.begin() + EncryptedDataChunk::VI_BYTE_SIZE,
      entireChunk.end());

  return EncryptedDataChunk(data, vi);
}