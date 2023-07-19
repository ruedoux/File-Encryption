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
  static bool encrypt_file(
    const std::string& filePath,
    const std::vector<BYTE> key);
  static bool decrypt_file(
    const std::string& filePath,
    const std::vector<BYTE> key);
};

#endif