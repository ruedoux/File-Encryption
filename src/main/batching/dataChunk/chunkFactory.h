#pragma once

#ifndef DATA_CHUNK_FACTORY
#define DATA_CHUNK_FACTORY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/exceptionHandling.h>

#include "encryptedDataChunk.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

template <class T>
struct ChunkContainer
{
  friend class ChunkFactory;

private:
  const T result;

public:
  ChunkContainer() noexcept {}
  ChunkContainer(T chunk) noexcept : result(chunk) {}

  T get_result() const noexcept
  {
    return result;
  }
};

class ChunkFactory
{
public:
  static ChunkContainer<DataChunk> get_chunk(
      const std::vector<BYTE> &data);
  static ChunkContainer<EncryptedDataChunk> get_chunk(
      const std::vector<BYTE> &data,
      const std::vector<BYTE> &vi);

  template <class T>
  static ChunkContainer<T> get_empty_chunk() noexcept
  {
    return ChunkContainer<T>();
  }
};

#endif