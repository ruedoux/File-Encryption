#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/logger.h>
#include <fileAccess.h>

#include "dataChunk/ChunkFactory.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class Batching
{
public:
  static u64 get_chunk_count_in_file(
      const std::string &filePath,
      const u64 chunkSize);

  template <class T>
  static void append_chunk_to_file(
      const std::string &filePath,
      const ChunkContainer<T> &chunkContainer)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePath);

    if (chunkContainer.is_error())
    {
      THROW_FILE_EXCEPTION("Chunk container has empty chunk.", filePath);
    }

    std::vector<BYTE> entireChunk = chunkContainer.get_result().get_entire_chunk();

    FileAccess::ErrorCode errorCode = FileAccess::append_bytes_to_file(
        filePath, entireChunk);

    if (errorCode != FileAccess::ErrorCode::OK)
    {
      THROW_FILE_EXCEPTION_WRITE(filePath, errorCode);
    }
  }

  template <class T>
  static ChunkContainer<T> read_chunk_from_file(
      const std::string &filePath,
      const u64 chunkIndex)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePath);

    std::vector<BYTE> readBytes;
    const std::uintmax_t chunkSize = T::get_desired_chunk_size();
    const std::uintmax_t fromIndex = chunkSize * chunkIndex;

    FileAccess::ErrorCode errorCode = FileAccess::read_bytes_from_file(
        filePath, readBytes, fromIndex, chunkSize);

    if (errorCode != FileAccess::ErrorCode::OK)
    {
      THROW_FILE_EXCEPTION_READ(filePath, fromIndex, chunkSize, errorCode);
    }

    ChunkContainer<T> chunkContainer = ChunkFactory::get_empty_chunk<T>();
    chunkContainer.get_result().map_from_bytes(readBytes);
    return chunkContainer;
  }
};

#endif
