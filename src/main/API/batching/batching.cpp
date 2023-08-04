#include "batching.h"

u64 Batching::get_chunk_count_in_file(
    const std::filesystem::path &filePath,
    const u64 chunkSize)
{
  THROW_EXCEPTION_IF_FILE_MISSING(filePath);

  std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
  std::uintmax_t totalChunkCount =
      fileSize / chunkSize + (fileSize % chunkSize != 0);
  return static_cast<u64>(totalChunkCount);
}

std::uintmax_t Batching::get_bytes_left_in_last_chunk(
    const std::filesystem::path &filePath,
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