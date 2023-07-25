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
      const u64 bytesToRead);

  template <class T>
  static void append_chunk_to_file(
      const std::string &filePath,
      const ChunkContainer<T> &chunkContainer)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePath);

    if (chunkContainer.get_result().get_entire_chunk().empty())
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
      const u64 chunkIndex,
      const u64 bytesToRead)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePath);

    std::vector<BYTE> readBytes;
    const std::uintmax_t fromIndex = bytesToRead * chunkIndex;

    FileAccess::ErrorCode errorCode = FileAccess::read_bytes_from_file(
        filePath, readBytes, fromIndex, bytesToRead);

    if (errorCode != FileAccess::ErrorCode::OK)
    {
      THROW_FILE_EXCEPTION_READ(filePath, fromIndex, bytesToRead, errorCode);
    }

    T chunk = ChunkFactory::get_empty_chunk<T>().get_result();;
    chunk.map_from_bytes(readBytes);
    return ChunkContainer<T>(chunk);
  }
};

#endif
