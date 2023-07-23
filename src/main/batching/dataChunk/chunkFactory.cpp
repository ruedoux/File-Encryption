#include "chunkFactory.h"

ChunkContainer<DataChunk> chunkFactory::get_chunk(
    const std::vector<BYTE> &data)
{
  ERROR_RETURN_IF_MORE(
      data.size(),
      DataChunk::DATA_BYTE_SIZE,
      ChunkContainer<DataChunk>::get_error());
  return ChunkContainer(DataChunk(data));
}

ChunkContainer<EncryptedDataChunk> chunkFactory::get_chunk(
    const std::vector<BYTE> &data,
    const std::vector<BYTE> &vi)
{
  ERROR_RETURN_IF_MORE(
      data.size(),
      DataChunk::DATA_BYTE_SIZE,
      ChunkContainer<EncryptedDataChunk>::get_error());
  ERROR_RETURN_IF_MORE(
      vi.size(),
      EncryptedDataChunk::VI_BYTE_SIZE,
      ChunkContainer<EncryptedDataChunk>::get_error())
  return ChunkContainer(EncryptedDataChunk(data, vi));
}