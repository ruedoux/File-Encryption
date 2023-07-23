#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/logger.h>
#include <fileAccess.h>

#include "dataChunk/chunkFactory.h"

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
  bool append_chunk_to_file(
      const std::string &filePath,
      const ChunkContainer<T> &chunkContainer)
  {
    if (chunkContainer.is_error())
    {
      Logger::get_instance().log_error(
          "Failed to write append to file: " + filePath,
          "Because chunk container has empty chunk.");
      return false;
    }

    std::vector<BYTE> entireChunk = chunkContainer.get_result().get_entire_chunk();

    FileAccess::ErrorCode errorCode =
        FileAccess::append_bytes_to_file(filePath, entireChunk);

    if (errorCode != FileAccess::ErrorCode::OK)
    {
      Logger::get_instance().log_error(
          "Failed to write append to file: " + filePath,
          "Write error code: " + std::to_string(errorCode));
      return false;
    }

    return true;
  }

  /*
  template <class T>
  ChunkContainer<T> read_chunk_from_file(
      const std::string &filePath,
      const u64 chunkIndex)
  {
    std::vector<BYTE> readBytes;

    FileAccess::ErrorCode errorCode =
        FileAccess::read_bytes_from_file(filePath, readBytes);
    
    return ChunkContainer<T>;
  }
  */
};

#endif
