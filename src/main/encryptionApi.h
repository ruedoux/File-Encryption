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
public:
  static void encrypt_file(
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> &key)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

    const u64 chunkSize = DataChunk::get_desired_chunk_size();
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
          (i == (chunkCount - 1)) ? get_bytes_left_in_last_chunk(filePathSource, chunkSize) : chunkSize;

      DataChunk chunk = Batching::read_chunk_from_file<DataChunk>(
          filePathSource, i, bytesToRead);
      
      Batching::append_chunk_to_file(
          filePathDestination, ChunkEncryption::encrypt_chunk(chunk, key));
    }
  }

  static void decrypt_file(
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> &key)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePathSource);

    const u64 chunkSize = EncryptedDataChunk::get_desired_chunk_size();
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
          (i == (chunkCount - 1)) ? get_bytes_left_in_last_chunk(filePathSource, chunkSize) : chunkSize;

      EncryptedDataChunk chunk = Batching::read_chunk_from_file<EncryptedDataChunk>(
          filePathSource, i, bytesToRead);
      
      Batching::append_chunk_to_file(
          filePathDestination, ChunkEncryption::decrypt_chunk(chunk, key));
    }
  }

private:
  static std::uintmax_t get_bytes_left_in_last_chunk(
      const std::string &filePath,
      const u64 chunkSize);
};

#endif