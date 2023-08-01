#pragma once

#ifndef FCCRYPT
#define FCCRYPT

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <crypto-algorithms/sha256.h>
#include <crypto-algorithms/aes.h>

#include <Api/global/global.h>

// --------------------------------------------
// Declarations
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
      const std::vector<BYTE>& bytes,
      const std::vector<BYTE>& key,
      const std::vector<BYTE>& vi);
  static std::vector<BYTE> decrypt(
      const std::vector<BYTE>& cryptedBytes,
      const std::vector<BYTE>& key,
      const std::vector<BYTE>& vi);
  static std::vector<BYTE> get_random_bytes(const u64 size);

private:
  static std::vector<BYTE> get_padded_bytes(
      const std::vector<BYTE>& bytes,
      u64 maxSize);
  static std::vector<BYTE> get_stretched_key(const std::vector<BYTE>& bytes);
  static std::vector<BYTE> get_hashed_key(const std::vector<BYTE>& bytes);
};

#endif
