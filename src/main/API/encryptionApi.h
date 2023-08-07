#pragma once

#ifndef ENCRYPTION_API
#define ENCRYPTION_API

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include "batching/batching.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class EncryptionApi
{
public:
  static void encrypt_file(
      const std::filesystem::path &filePathSource,
      const std::filesystem::path &filePathDestination,
      const std::vector<BYTE> &key);
  static void decrypt_file(
      const std::filesystem::path &filePathSource,
      const std::filesystem::path &filePathDestination,
      const std::vector<BYTE> &key);
};

#endif