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

    const u64 chunkCount = Batching::get_chunk_count_in_file(
        filePathSource, ChunkTypeFrom::get_desired_chunk_size());
    const u64 lastChunkIndex =
        chunkCount * ChunkTypeFrom::get_desired_chunk_size();
    const std::uintmax_t bytesLeftInLastChunk =
        FileAccess::get_byte_count_left_in_file(filePathSource, lastChunkIndex);

    if (!FileAccess::create_file(filePathDestination))
    {
      THROW_FILE_EXCEPTION("Unable to create file!", filePathDestination);
    }

    for (u64 i = 0; i < chunkCount; i++)
    {
      u64 chunkSize =
          (i == chunkCount - 1) ? bytesLeftInLastChunk : ChunkTypeFrom::get_desired_chunk_size();

      ChunkTypeFrom chunk = Batching::read_chunk_from_file<ChunkTypeFrom>(
          filePathSource, i, chunkSize);

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
};

#endif