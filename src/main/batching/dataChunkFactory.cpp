#include "dataChunkFactory.h"

const DataChunk DataChunkFactory::ErrorDataChunk =
    DataChunk(std::vector<BYTE>());
const CryptedDataChunk DataChunkFactory::ErrorCryptedDataChunk =
    CryptedDataChunk(std::vector<BYTE>(), std::vector<BYTE>());

DataChunk DataChunkFactory::get_DataChunk(
    std::vector<BYTE> &data)
{
  LOGGER_RETURN_IF_NOT_MATCH(
      data.size(),
      DataChunk::CHUNK_BYTE_SIZE,
      ErrorDataChunk)
  return DataChunk(data);
}

CryptedDataChunk DataChunkFactory::get_CryptedDataChunk(
    std::vector<BYTE> &data,
    std::vector<BYTE> &vi)
{
  LOGGER_RETURN_IF_NOT_MATCH(
      data.size(),
      CryptedDataChunk::DATA_BYTE_SIZE,
      ErrorCryptedDataChunk)
  LOGGER_RETURN_IF_NOT_MATCH(
      vi.size(),
      CryptedDataChunk::VI_BYTE_SIZE,
      ErrorCryptedDataChunk)
  return CryptedDataChunk(data, vi);
}

DataChunk DataChunkFactory::map_CryptedDataChunk_to_DataChunk(
    const CryptedDataChunk &cryptedDataChunk)
{
}

CryptedDataChunk DataChunkFactory::map_DataChunk_to_CryptedDataChunk(
    const DataChunk &dataChunk)
{
}