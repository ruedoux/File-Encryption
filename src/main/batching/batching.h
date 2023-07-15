#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>
#include <global/utils/logger.h>
#include <encryption.h>
#include <fileAccess.h>

#include "dataChunkFactory.h"

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

  std::uintmax_t get_chunk_count_in_file(const std::string &filePath);
  static bool write_append_chunk(
      const std::string &filePath,
      const DataChunk &dataChunk);
  static std::vector<BYTE> read_chunk(
      const std::string &filePath,
      const size_t chunkIndex);
};

#endif
