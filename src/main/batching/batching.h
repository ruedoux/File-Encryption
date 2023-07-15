#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include <global/global.h>
#include <global/logger.h>
#include <encryption.h>
#include <fileAccess.h>

#include "dataChunkFactory.h"

// --------------------------------------------
// DECLARATIONS
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
  bool save_chunk(const std::string &filePath, const DataChunk& dataChunk);

};

#endif
