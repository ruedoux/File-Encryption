#include "encryptionInterface.h"

bool EncryptionInterface::encrypt_file(
    const std::string &filePath,
    const std::vector<BYTE> key)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, false);

  return true;
}

bool EncryptionInterface::decrypt_file(
    const std::string &filePath,
    const std::vector<BYTE> key)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, false);
  return true;
}