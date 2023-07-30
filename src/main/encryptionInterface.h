#pragma once

#ifndef ENCRYPTION_INTERFACE
#define ENCRYPTION_INTERFACE

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <batching/batching.h>
#include <encryption/encryption.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

class EncryptionInterface
{
  typedef std::function<EncryptedDataChunk(const DataChunk &, const std::vector<BYTE> &)> EncryptionFunction;
  typedef std::function<DataChunk(const EncryptedDataChunk &, const std::vector<BYTE> &)> DecryptionFunction;

public:
  static const EncryptionFunction ENCRYPT_BIND;
  static const DecryptionFunction DECRYPT_BIND;

  template <class ChunkTypeFrom, class ChunkTypeTo>
  static void process_file(
      const std::function<ChunkTypeTo(const ChunkTypeFrom &, const std::vector<BYTE> &)> functionBind,
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> &key)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

    const u64 chunkSize = ChunkTypeFrom::get_desired_chunk_size();
    const u64 chunkCount = Batching::get_chunk_count_in_file(
        filePathSource, chunkSize);

    THROW_EXCEPTION_IF_TRUE(chunkCount == 0);

    if (!FileAccess::create_file(filePathDestination))
    {
      THROW_FILE_EXCEPTION("Unable to create file!", filePathDestination);
    }

    for (u64 i = 0; i < chunkCount; i++)
    {
      const u64 bytesToRead =
          (i == (chunkCount - 1)) ? get_bytes_left_in_last_chunk(filePathSource, chunkSize) : ChunkTypeFrom::get_desired_chunk_size();

      ChunkTypeFrom chunk = Batching::read_chunk_from_file<ChunkTypeFrom>(
          filePathSource, i, bytesToRead);
      Logger::log_info(std::to_string(i) + ", " + std::to_string(chunk.get_entire_chunk_size()));
      Batching::append_chunk_to_file(
          filePathDestination, functionBind(chunk, key));
    }
  }

private:
  static DataChunk decrypt_chunk(
      const EncryptedDataChunk &chunk,
      const std::vector<BYTE> &key);
  static EncryptedDataChunk encrypt_chunk(
      const DataChunk &chunk,
      const std::vector<BYTE> &key);
  static std::uintmax_t get_bytes_left_in_last_chunk(
      const std::string &filePath,
      const u64 chunkSize);
};

#endif