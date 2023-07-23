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

ChunkContainer<EncryptedDataChunk> chunkFactory::map_bytes_to_encrypted_chunk(
    const std::vector<BYTE> &bytes)
{
  ERROR_RETURN_IF_MORE(
      bytes.size(),
      EncryptedDataChunk::get_desired_chunk_size(),
      ChunkContainer<EncryptedDataChunk>::get_error());

  ERROR_RETURN_IF_LESS(
      bytes.size(),
      EncryptedDataChunk::VI_BYTE_SIZE,
      ChunkContainer<EncryptedDataChunk>::get_error());

  std::vector<BYTE> data;
  std::vector<BYTE> vi;

  vi.insert(
      vi.begin(),
      bytes.begin(),
      bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE);
  data.insert(
      data.begin(),
      bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE,
      bytes.end());

  return ChunkContainer(EncryptedDataChunk(data, vi));
}