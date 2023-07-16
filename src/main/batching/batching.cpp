#include "batching.h"

std::uintmax_t Batching::get_chunk_count_in_file(const std::string &filePath)
{
  std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
  std::uintmax_t totalChunkCount =
      fileSize / DecryptedDataChunk::CHUNK_BYTE_SIZE + (fileSize % DecryptedDataChunk::CHUNK_BYTE_SIZE != 0);
  return totalChunkCount;
}

bool Batching::write_append_chunk(
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
  LOGGER_RETURN_IF_FILE_NOT_OPEN(file, filePath, false);

  const std::vector<BYTE> &entireChunk = dataChunk.get_entire_chunk();
  file.write(reinterpret_cast<const char *>(entireChunk.data()), entireChunk.size());
  if (!file)
  {
    Logger::get_instance().log_error(
        "Failed to write append to file: ", filePath,
        ", data size: ", std::to_string(entireChunk.size()));
    return false;
  }

  return true;
}

std::vector<BYTE> Batching::read_data(
    const std::string &filePath,
    const size_t chunkIndex,
    const size_t chunkSize)
{
  std::ifstream file(filePath, READ_OPEN_MODE);
  LOGGER_RETURN_IF_FILE_NOT_OPEN(file, filePath, std::vector<BYTE>());

  std::vector<BYTE> data(chunkSize);
  const size_t chunkStartPos = chunkIndex * chunkSize;
  file.seekg(chunkStartPos);
  if (!file)
  {
    Logger::get_instance().log_error(
        "Failed to seekg in file: ", filePath,
        ", on position: ", std::to_string(chunkStartPos));
    return std::vector<BYTE>();
  }

  file.read(reinterpret_cast<char *>(data.data()), chunkSize);
  if (!file)
  {
    Logger::get_instance().log_error(
        "Failed to read from file: ", filePath,
        ", on position: ", std::to_string(chunkStartPos),
        ", chunk size:: ", std::to_string(chunkSize));
    return std::vector<BYTE>();
  }

  return data;
}