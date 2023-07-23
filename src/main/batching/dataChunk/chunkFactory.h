#pragma once

#ifndef DATA_CHUNK_FACTORY
#define DATA_CHUNK_FACTORY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/logger.h>

#include "encryptedDataChunk.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

template <class T>
struct ChunkContainer
{
  friend class chunkFactory;

private:
  T result;

  ChunkContainer() {}
  ChunkContainer(T chunk) : result(chunk) {}

public:
  static ChunkContainer get_error() { return ChunkContainer(); }
  bool is_error() const { return result.get_entire_chunk_size() == 0; }

  T get_result() const
  {
    return result;
  }
};

class chunkFactory
{
public:
  static ChunkContainer<DataChunk> get_chunk(
      const std::vector<BYTE> &data);
  static ChunkContainer<EncryptedDataChunk> get_chunk(
      const std::vector<BYTE> &data,
      const std::vector<BYTE> &vi);

  static ChunkContainer<EncryptedDataChunk> map_bytes_to_encrypted_chunk(
    const std::vector<BYTE> &bytes);
};

#endif