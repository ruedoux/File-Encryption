#pragma once

#ifndef BATCHING
#define BATCHING

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include "global.h"

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

    static constexpr size_t dataBytes = 1048560;
    static constexpr size_t viBytes = 16;
    static constexpr size_t chunkBytes = dataBytes + viBytes; // 1048576 Bytes

    static constexpr std::ios::openmode readMode =
        std::ios::binary;
    static constexpr std::ios::openmode writeMode =
        std::ios::binary;
    static constexpr std::ios::openmode writeAppendMode =
        std::ios::app | std::ios::binary;

    std::vector<BYTE> data;
    std::vector<BYTE> vi;
  };
};

#endif
