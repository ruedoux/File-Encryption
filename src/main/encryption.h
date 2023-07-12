/*
    Crypting operations
*/
#pragma once

#ifndef FCCRYPT
#define FCCRYPT

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include <crypto-algorithms/sha256.h>
#include <crypto-algorithms/aes.h>

#include "global.h"

// --------------------------------------------
// DECLARATIONS
// --------------------------------------------

class Encryption
{
private:
  Encryption() {}

public:
  static constexpr u64 KEY_BYTE_SIZE = 32;
  static constexpr u64 VI_BYTE_SIZE = 16;
  static constexpr u64 HASH_ROTATIONS = 32;

  static std::vector<BYTE> encrypt(
      const std::vector<BYTE> &bytes,
      std::vector<BYTE> key,
      std::vector<BYTE> vi);
  static std::vector<BYTE> decrypt(
      const std::vector<BYTE> &cryptedBytes,
      std::vector<BYTE> key,
      std::vector<BYTE> vi);
  static std::vector<BYTE> get_random_bytes(u64 size);

private:
  static std::vector<BYTE> get_padded_bytes(
      const std::vector<BYTE> bytes,
      u64 maxSize);
  static std::vector<BYTE> get_stretched_key(std::vector<BYTE> bytes);
  static std::vector<BYTE> get_hashed_key(std::vector<BYTE> bytes);
};

#endif
