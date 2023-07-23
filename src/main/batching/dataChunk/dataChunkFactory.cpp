#include "dataChunkFactory.h"

const DataChunk DataChunk::ErrorDataChunk =
    DataChunk(std::vector<BYTE>());
const EncryptedDataChunk EncryptedDataChunk::ErrorEncryptedDataChunk =
    EncryptedDataChunk(std::vector<BYTE>(), std::vector<BYTE>());

DataChunk DataChunkFactory::get_DataChunk(
    const std::vector<BYTE> &data)
{
  ERROR_RETURN_IF_CONDITION_TRUE(
      data.size() > DataChunk::DATA_BYTE_SIZE,
      DataChunk::ErrorDataChunk,
      "Provided chunk size is over the bound limit!",
      "Chunk size: " + std::to_string(data.size()),
      "Max size: " + std::to_string(DataChunk::DATA_BYTE_SIZE))
  return DataChunk(data);
}

EncryptedDataChunk DataChunkFactory::get_EncryptedDataChunk(
    const std::vector<BYTE> &data,
    const std::vector<BYTE> &vi)
{
  ERROR_RETURN_IF_CONDITION_TRUE(
      data.size() > EncryptedDataChunk::DATA_BYTE_SIZE,
      EncryptedDataChunk::ErrorEncryptedDataChunk,
      "Provided encrypted data size is over the bound limit!",
      "Chunk size: " + std::to_string(data.size()),
      "Max size: " + std::to_string(EncryptedDataChunk::DATA_BYTE_SIZE))
  ERROR_RETURN_IF_NOT_MATCH(
      vi.size(),
      EncryptedDataChunk::VI_BYTE_SIZE,
      EncryptedDataChunk::ErrorEncryptedDataChunk)
  return EncryptedDataChunk(data, vi);
}