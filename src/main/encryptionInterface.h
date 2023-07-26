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
  static void encrypt_file(
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> &key);
  static void decrypt_file(
      const std::string &filePathSource,
      const std::string &filePathDestination,
      const std::vector<BYTE> &key);

private:
  static DataChunk decrypt_chunk(
      const EncryptedDataChunk &chunk,
      const std::vector<BYTE> &key);
  static EncryptedDataChunk encrypt_chunk(
      const DataChunk &chunk,
      const std::vector<BYTE> &key);
};

#endif