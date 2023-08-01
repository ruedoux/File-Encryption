#include "ChunkFactory.h"

DataChunk ChunkFactory::get_chunk(
    const std::vector<BYTE> &data)
{
  THROW_EXCEPTION_IF_MORE(data.size(), DataChunk::DATA_BYTE_SIZE);
  return DataChunk(data);
}

EncryptedDataChunk ChunkFactory::get_chunk(
    const std::vector<BYTE> &data,
    const std::vector<BYTE> &vi)
{
  THROW_EXCEPTION_IF_MORE(data.size(), DataChunk::DATA_BYTE_SIZE);
  THROW_EXCEPTION_IF_MORE(vi.size(), EncryptedDataChunk::VI_BYTE_SIZE);
  return EncryptedDataChunk(data, vi);
}