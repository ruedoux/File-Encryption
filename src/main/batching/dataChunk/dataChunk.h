#pragma once

#ifndef DATA_CHUNK
#define DATA_CHUNK

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

template <class T>
struct ChunkContainer;

struct DataChunk
{
  friend class chunkFactory;
  friend class ChunkContainer<DataChunk>;

  static constexpr std::uintmax_t DATA_BYTE_SIZE =
      static_cast<std::uintmax_t>(MiB(1));

protected:
  std::vector<BYTE> data;
  DataChunk(const std::vector<BYTE> data) : data(data) {}
  DataChunk() {}

public:
  std::vector<BYTE> get_data() const { return data; }
  virtual std::vector<BYTE> get_entire_chunk() const { return data; }
  virtual u64 get_entire_chunk_size() const { return data.size(); }

  bool operator==(const DataChunk &other) const
  {
    return other.get_entire_chunk() == this->get_entire_chunk();
  }

  bool operator!=(const DataChunk &other) const
  {
    return other.get_entire_chunk() != this->get_entire_chunk();
  }
};

#endif