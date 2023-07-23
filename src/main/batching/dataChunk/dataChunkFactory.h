#pragma once

#ifndef DATA_CHUNK_FACTORY
#define DATA_CHUNK_FACTORY

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <global/global.h>
#include <global/logging/errorHandling.h>
#include <encryption/encryption.h>

#include "encryptedDataChunk.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

struct ChunkContainer
{
private:
  DataChunk result;

public:
  bool is_error() { return result.get_entire_chunk_size() == 0; }
  DataChunk get_result() { return result; }
};

class DataChunkFactory
{
public:
  static DataChunk get_DataChunk(
      const std::vector<BYTE> &data);
  static EncryptedDataChunk get_EncryptedDataChunk(
      const std::vector<BYTE> &data,
      const std::vector<BYTE> &vi);
};

#endif