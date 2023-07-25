#pragma once

#ifndef ENCRYPTION_INTERFACE
#define ENCRYPTION_INTERFACE

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <batching/batching.h>
#include <encryption/encryption.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

class EncryptionInterface
{
public:
  static bool encrypt_file(
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> key);
  static bool decrypt_file(
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> key);
};

#endif