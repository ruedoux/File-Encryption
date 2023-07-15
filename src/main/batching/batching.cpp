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
  if (!file.is_open())
  {
    Logger::get_instance().log_error(
        LOGGER_GET_LINE, "Failed to open file: ", filePath);
    return false;
  }

  const std::vector<BYTE> &entireChunk = dataChunk.get_entire_chunk();
  file.write(reinterpret_cast<const char *>(&entireChunk[0]), entireChunk.size());
  file.close();
  return true;
}
/*
std::vector<BYTE> Batching::read_chunk(
    const std::string &filePath,
    const size_t chunkIndex)
{
  std::vector<unsigned char> data(chunkBytes);

  if (!(GLOBAL::check_multiplication_overflow(chunkBytes, dataIndex)))
  {
    
  }
  size_t startPos = chunkBytes * dataIndex;

  std::ifstream file(filePath, Chunk::readMode);
  if (!file)
  {
    cpprintn("File called: " + std::string(filePath) + ", doesn't exist.\n Aborting program.");
    exit(0);
  }

  // Assert whether the next data of data is 1MB or less, if less only allocate the size needed.
  size_t dataToRead = chunkBytes;
  size_t fileSize = FileManager::get_file_size(filePath);
  size_t fileRemaining = fileSize - chunkBytes * dataIndex;
  if (chunkBytes > fileRemaining)
  {
    dataToRead = fileRemaining;
    data.resize(dataToRead);
  }

  file.seekg(startPos);                      // Go to the current data
  file.read((char *)(&data[0]), dataToRead); // Read data

  file.close();
  return data;
}*/