#include "encryptionApi.h"

std::uintmax_t EncryptionApi::get_bytes_left_in_last_chunk(
    const std::string &filePath,
    const u64 chunkSize)
{
  const std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
  std::uintmax_t bytesLeft = fileSize % chunkSize;
  if ((fileSize > 0) && (bytesLeft == 0))
  {
    bytesLeft = chunkSize;
  }
  return bytesLeft;
}