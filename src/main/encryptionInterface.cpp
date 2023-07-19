#include "encryptionInterface.h"

bool EncryptionInterface::encrypt_file(
    const std::string &filePath,
    const std::vector<BYTE> key)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, false);

  uintmax_t chunkCount = Batching::get_chunk_count_in_file(filePath);
  return true;
}

bool EncryptionInterface::decrypt_file(
    const std::string &filePath,
    const std::vector<BYTE> key)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, false);
  return true;
}