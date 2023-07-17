#include "dataChunkFactory.h"

const DataChunk DataChunk::ErrorDataChunk =
    DataChunk(std::vector<BYTE>());
const EncryptedDataChunk EncryptedDataChunk::ErrorEncryptedDataChunk =
    EncryptedDataChunk(std::vector<BYTE>(), std::vector<BYTE>());

DataChunk DataChunkFactory::get_DataChunk(
    const std::vector<BYTE> &data)
{
  ERROR_RETURN_IF_NOT_MATCH(
      data.size(),
      DataChunk::CHUNK_BYTE_SIZE,
      DataChunk::ErrorDataChunk)
  return DataChunk(data);
}

EncryptedDataChunk DataChunkFactory::get_EncryptedDataChunk(
    const std::vector<BYTE> &data,
    const std::vector<BYTE> &vi)
{
  ERROR_RETURN_IF_NOT_MATCH(
      data.size(),
      EncryptedDataChunk::DATA_BYTE_SIZE,
      EncryptedDataChunk::ErrorEncryptedDataChunk)
  ERROR_RETURN_IF_NOT_MATCH(
      vi.size(),
      EncryptedDataChunk::VI_BYTE_SIZE,
      EncryptedDataChunk::ErrorEncryptedDataChunk)
  return EncryptedDataChunk(data, vi);
}

DataChunk DataChunkFactory::map_EncryptedDataChunk_to_DataChunk(
    const EncryptedDataChunk &encryptedDataChunk)
{
  const std::vector<BYTE> &entireChunk = encryptedDataChunk.get_entire_chunk();
  return get_DataChunk(entireChunk);
}

EncryptedDataChunk DataChunkFactory::map_DataChunk_to_EncryptedDataChunk(
    const DataChunk &dataChunk)
{
  const std::vector<BYTE> &entireChunk = dataChunk.get_entire_chunk();

  const std::vector<BYTE> vi(
      entireChunk.begin(),
      entireChunk.begin() + EncryptedDataChunk::VI_BYTE_SIZE);

  const std::vector<BYTE> data(
      entireChunk.begin() + EncryptedDataChunk::VI_BYTE_SIZE,
      entireChunk.end());

  return get_EncryptedDataChunk(data, vi);
}