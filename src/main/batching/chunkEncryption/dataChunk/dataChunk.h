#pragma once

#ifndef DATA_CHUNK
#define DATA_CHUNK

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/exceptionHandling.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

template <class T>
struct chunk;

struct DataChunk
{
  friend class ChunkFactory;
  friend class chunk<DataChunk>;

  static constexpr u64 DATA_BYTE_SIZE = static_cast<u64>(10);

protected:
  std::vector<BYTE> data;

  DataChunk(const std::vector<BYTE> data) noexcept : data(data) {}
  DataChunk() noexcept {}

  void set_data(const std::vector<BYTE> &newData)
  {
    THROW_EXCEPTION_IF_MORE(newData.size(), DATA_BYTE_SIZE);
    data = newData;
  }

public:
  std::vector<BYTE> get_data() const noexcept { return data; }

  virtual std::vector<BYTE> get_entire_chunk() const { return data; }

  virtual u64 get_entire_chunk_size() const noexcept { return data.size(); }

  static u64 get_desired_chunk_size() noexcept { return DATA_BYTE_SIZE; }

  virtual void map_from_bytes(const std::vector<BYTE> &bytes)
  {
    set_data(bytes);
  }

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