#pragma once

#ifndef DATA_CHUNK
#define DATA_CHUNK

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include <global/global.h>
#include <global/logger.h>
#include <encryption.h>

// --------------------------------------------
// DECLARATIONS
// --------------------------------------------

struct DataChunk
{
  friend class DataChunkFactory;

protected:
  std::vector<BYTE> data;
  DataChunk(std::vector<BYTE> data) : data(data) {}

public:
  static constexpr std::uintmax_t CHUNK_BYTE_SIZE =
      static_cast<std::uintmax_t>(MiB(1));

  std::vector<BYTE> get_data() const { return data; }
  virtual std::vector<BYTE> get_entire_chunk() const { return data; }
};

struct CryptedDataChunk : DataChunk
{
  friend class DataChunkFactory;

protected:
  std::vector<BYTE> vi;
  CryptedDataChunk(std::vector<BYTE> data, std::vector<BYTE> vi)
      : DataChunk(data), vi(vi) {}

public:
  static constexpr std::uintmax_t VI_BYTE_SIZE =
      static_cast<std::uintmax_t>(Encryption::VI_BYTE_SIZE);
  static constexpr std::uintmax_t DATA_BYTE_SIZE =
      CHUNK_BYTE_SIZE - VI_BYTE_SIZE;

  std::vector<BYTE> get_vi() const { return vi; }

  std::vector<BYTE> get_entire_chunk() const override
  {
    std::vector<BYTE> entireChunk(vi.size() + data.size());

    entireChunk.insert(entireChunk.end(), vi.begin(), vi.end());
    entireChunk.insert(entireChunk.end(), data.begin(), data.end());

    return entireChunk;
  }
};

class DataChunkFactory
{
public:
  static const DataChunk ErrorDataChunk;
  static const CryptedDataChunk ErrorCryptedDataChunk;

  static DataChunk get_DataChunk(
      std::vector<BYTE> &data);
  static CryptedDataChunk get_CryptedDataChunk(
      std::vector<BYTE> &data,
      std::vector<BYTE> &vi);

  static DataChunk map_CryptedDataChunk_to_DataChunk(
      const CryptedDataChunk &cryptedDataChunk);
  static CryptedDataChunk map_DataChunk_to_CryptedDataChunk(
      const DataChunk &dataChunk);
};

#endif