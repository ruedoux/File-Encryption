#pragma once

#ifndef DATA_CHUNK
#define DATA_CHUNK

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>
#include <global/utils/logger.h>
#include <encryption.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

struct DataChunk
{
  static constexpr std::uintmax_t CHUNK_BYTE_SIZE =
      static_cast<std::uintmax_t>(MiB(1));

protected:
  std::vector<BYTE> data;
  DataChunk(const std::vector<BYTE> data) : data(data) {}

public:
  std::vector<BYTE> get_data() const { return data; }
  virtual std::vector<BYTE> get_entire_chunk() const = 0;

  bool operator==(const DataChunk &other) const
  {
    return other.get_entire_chunk() == this->get_entire_chunk();
  }

  bool operator!=(const DataChunk &other) const
  {
    return other.get_entire_chunk() != this->get_entire_chunk();
  }
};

struct DecryptedDataChunk : DataChunk
{
  friend class DataChunkFactory;

private:
  DecryptedDataChunk(const std::vector<BYTE> data) : DataChunk(data) {}

public:
  std::vector<BYTE> get_entire_chunk() const override { return data; }
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
  static const DecryptedDataChunk ErrorDecryptedDataChunk;
  static const EncryptedDataChunk ErrorEncryptedDataChunk;

  static DecryptedDataChunk get_DecryptedDataChunk(
      const std::vector<BYTE>& data);
  static EncryptedDataChunk get_EncryptedDataChunk(
      const std::vector<BYTE>& data,
      const std::vector<BYTE>& vi);

  static DecryptedDataChunk map_EncryptedDataChunk_to_DecryptedDataChunk(
      const EncryptedDataChunk& encryptedDataChunk);
  static EncryptedDataChunk map_DecryptedDataChunk_to_EncryptedDataChunk(
      const DecryptedDataChunk& decryptedDataChunk);
};

#endif