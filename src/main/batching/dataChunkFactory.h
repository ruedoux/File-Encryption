#pragma once

#ifndef DATA_CHUNK
#define DATA_CHUNK

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>
#include <global/logging/errorHandling.h>

#include "encryption/encryption.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

struct DataChunk
{
  friend class DataChunkFactory;

  static constexpr std::uintmax_t CHUNK_BYTE_SIZE =
      static_cast<std::uintmax_t>(MiB(1));

protected:
  std::vector<BYTE> data;
  DataChunk(const std::vector<BYTE> data) : data(data) {}

public:
  static const DataChunk ErrorDataChunk;

  std::vector<BYTE> get_data() const { return data; }

  virtual std::vector<BYTE> get_entire_chunk() const { return data; }

  bool operator==(const DataChunk &other) const
  {
    return other.get_entire_chunk() == this->get_entire_chunk();
  }

  bool operator!=(const DataChunk &other) const
  {
    return other.get_entire_chunk() != this->get_entire_chunk();
  }
};

struct EncryptedDataChunk : DataChunk
{
  friend class DataChunkFactory;

  static constexpr std::uintmax_t VI_BYTE_SIZE =
      static_cast<std::uintmax_t>(Encryption::VI_BYTE_SIZE);
  static constexpr std::uintmax_t DATA_BYTE_SIZE =
      CHUNK_BYTE_SIZE - VI_BYTE_SIZE;

private:
  std::vector<BYTE> vi;
  EncryptedDataChunk(const std::vector<BYTE> data, const std::vector<BYTE> vi)
      : DataChunk(data), vi(vi) {}

public:
  static const EncryptedDataChunk ErrorEncryptedDataChunk;

  std::vector<BYTE> get_vi() const { return vi; }

  std::vector<BYTE> get_entire_chunk() const override
  {
    std::vector<BYTE> entireChunk;

    entireChunk.insert(entireChunk.end(), vi.begin(), vi.end());
    entireChunk.insert(entireChunk.end(), data.begin(), data.end());

    return entireChunk;
  }
};

class DataChunkFactory
{
public:
  static DataChunk get_DataChunk(
      const std::vector<BYTE> &data);
  static EncryptedDataChunk get_EncryptedDataChunk(
      const std::vector<BYTE> &data,
      const std::vector<BYTE> &vi);

  static DataChunk map_EncryptedDataChunk_to_DataChunk(
      const EncryptedDataChunk &encryptedDataChunk);
  static EncryptedDataChunk map_DataChunk_to_EncryptedDataChunk(
      const DataChunk &dataChunk);
};

#endif