#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "fileAccess/fileAccess.h"
#include "chunkEncryption/chunkEncryption.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class Batching
{
public:
  static u64 get_chunk_count_in_file(
      const std::string &filePath,
      const u64 bytesToRead);

  static std::uintmax_t get_bytes_left_in_last_chunk(
      const std::string &filePath,
      const u64 chunkSize);

  template <class ChunkType>
  static void append_chunk_to_file(
      const std::string &filePath,
      const ChunkType &chunk)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePath);

    if (chunk.get_entire_chunk().empty())
    {
      THROW_FILE_EXCEPTION("Chunk container has empty chunk.", filePath);
    }

    std::vector<BYTE> entireChunk = chunk.get_entire_chunk();

    FileAccess::ErrorCode errorCode = FileAccess::append_bytes_to_file(
        filePath, entireChunk);

    if (errorCode != FileAccess::ErrorCode::OK)
    {
      THROW_FILE_EXCEPTION_WRITE(filePath, errorCode);
    }
  }

  template <class ChunkType>
  static ChunkType read_chunk_from_file(
      const std::string &filePath,
      const u64 chunkIndex,
      const u64 bytesToRead)
  {
    THROW_EXCEPTION_IF_FILE_MISSING(filePath);

    const std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
    const std::uintmax_t fromIndex =
        ChunkType::get_desired_chunk_size() * chunkIndex;
    
    THROW_EXCEPTION_IF_MORE(fromIndex + bytesToRead, fileSize);

    std::vector<BYTE> readBytes;
    FileAccess::ErrorCode errorCode = FileAccess::read_bytes_from_file(
        filePath, readBytes, fromIndex, bytesToRead);

    if (errorCode != FileAccess::ErrorCode::OK)
    {
      THROW_FILE_EXCEPTION_READ(filePath, fromIndex, bytesToRead, errorCode);
    }

    ChunkType chunk = ChunkFactory::get_empty_chunk<ChunkType>();
    chunk.map_from_bytes(readBytes);
    return chunk;
  }
};

#endif
