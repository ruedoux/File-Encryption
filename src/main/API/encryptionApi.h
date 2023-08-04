#pragma once

#ifndef ENCRYPTION_API
#define ENCRYPTION_API

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "batching/batching.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class EncryptionApi
{
  typedef std::function<EncryptedDataChunk(const DataChunk &, const std::vector<BYTE> &)> EncryptionFunction;
  typedef std::function<DataChunk(const EncryptedDataChunk &, const std::vector<BYTE> &)> DecryptionFunction;
  
  static const EncryptionFunction ENCRYPT_BIND;
  static const DecryptionFunction DECRYPT_BIND;

public:
  static void encrypt_file(
      const std::filesystem::path &filePathSource,
      const std::filesystem::path &filePathDestination,
      const std::vector<BYTE> &key);
  static void decrypt_file(
      const std::filesystem::path &filePathSource,
      const std::filesystem::path &filePathDestination,
      const std::vector<BYTE> &key);

private:
  template <class ChunkTypeFrom, class ChunkTypeTo>
  static void process_and_append_chunk_to_file(
      const std::function<ChunkTypeTo(const ChunkTypeFrom &, const std::vector<BYTE> &)> functionBind,
      const std::filesystem::path &filePathSource,
      const std::filesystem::path &filePathDestination,
      const std::vector<BYTE> &key,
      const u64 chunkIndex)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);
    THROW_EXCEPTION_IF_FILE_MISSING(filePathDestination);

    const u64 chunkSizeFrom = ChunkTypeFrom::get_desired_chunk_size();
    const uintmax_t fileSize = FileAccess::get_file_size(filePathSource);
    const u64 maxChunks = Batching::get_chunk_count_in_file(filePathSource, chunkSizeFrom);
    const uintmax_t lastByteIndex = chunkSizeFrom * chunkIndex + chunkSizeFrom;

    THROW_EXCEPTION_IF_MORE(chunkIndex, maxChunks);
    THROW_EXCEPTION_IF_TRUE(fileSize == 0);

    const u64 bytesToRead =
        (lastByteIndex < fileSize) ? chunkSizeFrom : chunkSizeFrom - (lastByteIndex - fileSize);

    const ChunkTypeFrom chunk = Batching::read_chunk_from_file<ChunkTypeFrom>(
        filePathSource, chunkIndex, bytesToRead);

    Batching::append_chunk_to_file(
        filePathDestination, functionBind(chunk, key));
  }
};

#endif