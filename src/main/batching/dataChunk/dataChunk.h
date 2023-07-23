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

  static constexpr u64 DATA_BYTE_SIZE = static_cast<u64>(MiB(1));

protected:
  std::vector<BYTE> data;

  DataChunk(const std::vector<BYTE> data) : data(data) {}
  DataChunk() {}

  bool set_data(std::vector<BYTE> newData)
  {
    if (newData.size() > DATA_BYTE_SIZE)
    {
      return false;
    }

    data = newData;
    return true;
  }

public:
  std::vector<BYTE> get_data() const { return data; }

  virtual std::vector<BYTE> get_entire_chunk() const { return data; }

  virtual u64 get_entire_chunk_size() const { return data.size(); }

  static u64 get_desired_chunk_size() { return DATA_BYTE_SIZE; }

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