#pragma once

#ifndef DATA_CHUNK_FACTORY
#define DATA_CHUNK_FACTORY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "encryptedDataChunk.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ChunkFactory
{
public:
  static DataChunk get_chunk(
      const std::vector<BYTE> &data);
  static EncryptedDataChunk get_chunk(
      const std::vector<BYTE> &data,
      const std::vector<BYTE> &vi);

  template <class ChunkType>
  static ChunkType get_empty_chunk() noexcept
  {
    return ChunkType();
  }
};

#endif