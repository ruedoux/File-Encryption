#include "batching.h"

std::uintmax_t Batching::get_chunk_count_in_file(const std::string &filePath)
{
  std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
  std::uintmax_t totalChunkCount =
      fileSize / DataChunk::CHUNK_BYTE_SIZE + (fileSize % DataChunk::CHUNK_BYTE_SIZE != 0);
  return totalChunkCount;
}

bool Batching::save_chunk(
    const std::string &filePath,
    const DataChunk &dataChunk)
{
  if (!FileAccess::file_exist(filePath))
  {
    Logger::get_instance().log_error(
        LOGGER_GET_LINE, "File is missing: ", filePath);
    return false;
  }

  std::ofstream file(filePath, WRITE_APPEND_OPEN_MODE);
  if (!file.is_open())
  {
    Logger::get_instance().log_error(
        LOGGER_GET_LINE, "Failed to open file: ", filePath);
    return false;
  }

  std::vector<BYTE> entireChunk = dataChunk.get_entire_chunk();
  file.write(reinterpret_cast<const char *>(&entireChunk[0]), entireChunk.size());
  file.close();
  return true;
}