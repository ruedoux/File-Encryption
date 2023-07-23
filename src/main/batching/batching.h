#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>
#include <global/logging/errorHandling.h>
#include <fileAccess.h>

#include "dataChunk/dataChunkFactory.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class Batching
{
public:
  static constexpr std::ios::openmode READ_OPEN_MODE =
      std::ios::binary;
  static constexpr std::ios::openmode WRITE_OPEN_MODE =
      std::ios::binary;
  static constexpr std::ios::openmode WRITE_APPEND_OPEN_MODE =
      std::ios::app | std::ios::binary;

  static u64 get_chunk_count_in_file(
    const std::string &filePath,
    const u64 chunkSize);
  static bool write_append_chunk(
      const std::string &filePath,
      const DataChunk &dataChunk);
  static DataChunk read_data(
      const std::string &filePath,
      const size_t chunkIndex);
};

#endif
