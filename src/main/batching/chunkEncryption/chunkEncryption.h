#pragma once

#ifndef CHUNK_ENCRYPTION
#define CHUNK_ENCRYPTION

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "dataChunk/chunkFactory.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ChunkEncryption
{
public:
  static DataChunk decrypt_chunk(
      const EncryptedDataChunk &chunk,
      const std::vector<BYTE> &key);
  static EncryptedDataChunk encrypt_chunk(
      const DataChunk &chunk,
      const std::vector<BYTE> &key);
};

#endif