#include "dataChunkFactory.h"

const DecryptedDataChunk DataChunkFactory::ErrorDecryptedDataChunk =
    DecryptedDataChunk(std::vector<BYTE>());
const EncryptedDataChunk DataChunkFactory::ErrorEncryptedDataChunk =
    EncryptedDataChunk(std::vector<BYTE>(), std::vector<BYTE>());

DecryptedDataChunk DataChunkFactory::get_DecryptedDataChunk(
    const std::vector<BYTE> &data)
{
  LOGGER_RETURN_IF_NOT_MATCH(
      data.size(),
      DecryptedDataChunk::CHUNK_BYTE_SIZE,
      ErrorDecryptedDataChunk)
  return DecryptedDataChunk(data);
}

EncryptedDataChunk DataChunkFactory::get_EncryptedDataChunk(
    const std::vector<BYTE> &data,
    const std::vector<BYTE> &vi)
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
  const std::vector<BYTE> &entireChunk = encryptedDataChunk.get_entire_chunk();
  return get_DecryptedDataChunk(entireChunk);
}

EncryptedDataChunk DataChunkFactory::map_DecryptedDataChunk_to_EncryptedDataChunk(
    const DecryptedDataChunk &decryptedDataChunk)
{
  const std::vector<BYTE> &entireChunk = decryptedDataChunk.get_entire_chunk();

  const std::vector<BYTE> vi(
      entireChunk.begin(),
      entireChunk.begin() + EncryptedDataChunk::VI_BYTE_SIZE);

  const std::vector<BYTE> data(
      entireChunk.begin() + EncryptedDataChunk::VI_BYTE_SIZE,
      entireChunk.end());

  return get_EncryptedDataChunk(data, vi);
}