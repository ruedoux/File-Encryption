#pragma once

#ifndef ENCRYPTED_DATA_CHUNK
#define ENCRYPTED_DATA_CHUNK

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>
#include <encryption/encryption.h>

#include "dataChunk.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

template <class T>
struct ChunkContainer;

struct EncryptedDataChunk : DataChunk
{
  friend class chunkFactory;
  friend class ChunkContainer<EncryptedDataChunk>;

  static constexpr u64 VI_BYTE_SIZE = Encryption::VI_BYTE_SIZE;

protected:
  std::vector<BYTE> vi;
  
  EncryptedDataChunk(const std::vector<BYTE> data, const std::vector<BYTE> vi)
      : DataChunk(data), vi(vi) {}

  EncryptedDataChunk() {}

  bool set_vi(std::vector<BYTE> newVi)
  {
    if (newVi.size() != VI_BYTE_SIZE)
    {
      return false;
    }

    vi = newVi;
    return true;
  }

public:
  std::vector<BYTE> get_vi() const { return vi; }

  virtual u64 get_entire_chunk_size() const override
  {
    return data.size() + vi.size();
  }

  static u64 get_desired_chunk_size()
  {
    return DATA_BYTE_SIZE + VI_BYTE_SIZE;
  }

  std::vector<BYTE> get_entire_chunk() const override
  {
    std::vector<BYTE> entireChunk;

    entireChunk.insert(entireChunk.end(), vi.begin(), vi.end());
    entireChunk.insert(entireChunk.end(), data.begin(), data.end());

    return entireChunk;
  }
};

#endif