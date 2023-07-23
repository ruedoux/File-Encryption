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

  static constexpr std::uintmax_t VI_BYTE_SIZE =
      static_cast<std::uintmax_t>(Encryption::VI_BYTE_SIZE);

private:
  std::vector<BYTE> vi;
  EncryptedDataChunk(const std::vector<BYTE> data, const std::vector<BYTE> vi)
      : DataChunk(data), vi(vi) {}
  EncryptedDataChunk() {}

public:
  std::vector<BYTE> get_vi() const { return vi; }
  virtual u64 get_entire_chunk_size() const { return data.size() + vi.size(); }

  std::vector<BYTE> get_entire_chunk() const override
  {
    std::vector<BYTE> entireChunk;

    entireChunk.insert(entireChunk.end(), vi.begin(), vi.end());
    entireChunk.insert(entireChunk.end(), data.begin(), data.end());

    return entireChunk;
  }
};

#endif