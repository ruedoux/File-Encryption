#pragma once

#ifndef ENCRYPTED_DATA_CHUNK
#define ENCRYPTED_DATA_CHUNK

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/global/exceptionHandling.h>

#include "encryption/encryption.h"
#include "dataChunk.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

template <class T>
struct chunk;

struct EncryptedDataChunk : DataChunk
{
  friend class ChunkFactory;
  friend class chunk<EncryptedDataChunk>;

  static constexpr u64 VI_BYTE_SIZE = Encryption::VI_BYTE_SIZE;

protected:
  std::vector<BYTE> vi;

  EncryptedDataChunk(const std::vector<BYTE> data, const std::vector<BYTE> vi) noexcept
      : DataChunk(data), vi(vi) {}

  EncryptedDataChunk() noexcept {}

  void set_vi(const std::vector<BYTE> &newVi)
  {
    THROW_EXCEPTION_IF_NOT_MATCH(newVi.size(), VI_BYTE_SIZE);
    vi = newVi;
  }

public:
  std::vector<BYTE> get_vi() const noexcept { return vi; }

  virtual u64 get_entire_chunk_size() const noexcept override
  {
    return data.size() + vi.size();
  }

  static u64 get_desired_chunk_size() noexcept
  {
    return DATA_BYTE_SIZE + VI_BYTE_SIZE;
  }

  virtual void map_from_bytes(const std::vector<BYTE> &bytes) override
  {
    THROW_EXCEPTION_IF_TRUE(bytes.empty());
    
    std::vector<BYTE> newVi(
        bytes.begin(), bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE);
    std::vector<BYTE> newData(
        bytes.begin() + EncryptedDataChunk::VI_BYTE_SIZE, bytes.end());

    set_data(newData);
    set_vi(newVi);
  }

  virtual std::vector<BYTE> get_entire_chunk() const override
  {
    std::vector<BYTE> entireChunk;

    entireChunk.insert(entireChunk.end(), vi.begin(), vi.end());
    entireChunk.insert(entireChunk.end(), data.begin(), data.end());

    return entireChunk;
  }
};

#endif