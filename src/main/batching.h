#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include "global.h"
#include "encryption.h"
#include "fileAccess.h"

// --------------------------------------------
// DECLARATIONS
// --------------------------------------------

class Batching
{
  struct Chunk
  {
    /*
    data (1MB) || (1,048,575B):
    - 16 Bytes vi
    - Up to 1048559 Bytes of data
    */

    static constexpr size_t VI_BYTE_SIZE = Encryption::VI_BYTE_SIZE;
    static constexpr size_t DATA_BYTE_SIZE = MiB(1) - VI_BYTE_SIZE;
    static constexpr size_t CHUNK_BYTE_SIZE = MiB(1);

    std::vector<BYTE> data;
    std::vector<BYTE> vi;
  };
};

#endif
