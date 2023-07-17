#include "batching.h"

std::uintmax_t Batching::get_chunk_count_in_file(const std::string &filePath)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, -1);

  std::uintmax_t fileSize = FileAccess::get_file_size(filePath);
  std::uintmax_t totalChunkCount =
      fileSize / DataChunk::CHUNK_BYTE_SIZE + (fileSize % DataChunk::CHUNK_BYTE_SIZE != 0);
  return totalChunkCount;
}

bool Batching::write_append_chunk(
    const std::string &filePath,
    const DataChunk &dataChunk)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, -1);

  std::ofstream file(filePath, WRITE_APPEND_OPEN_MODE);
  ERROR_RETURN_IF_FILE_NOT_OPEN(file, filePath, false);

  const std::vector<BYTE> &entireChunk = dataChunk.get_entire_chunk();

  ERROR_RETURN_IF_FILE_OPERATION_FAILED(
      file.write(reinterpret_cast<const char *>(entireChunk.data()), entireChunk.size()),
      false,
      "Failed to write append to file: ", filePath,
      ", data size: ", std::to_string(entireChunk.size()))

  return true;
}

DataChunk Batching::read_data(
    const std::string &filePath,
    const size_t chunkIndex)
{
  ERROR_RETURN_IF_FILE_NOT_EXIST(filePath, DataChunk::ErrorDataChunk);

  std::ifstream file(filePath, READ_OPEN_MODE);
  ERROR_RETURN_IF_FILE_NOT_OPEN(file, filePath, DataChunk::ErrorDataChunk);

  const std::uintmax_t chunkCountInFile = get_chunk_count_in_file(filePath);
  ERROR_RETURN_IF_CONDITION_TRUE(
      chunkCountInFile < chunkIndex,
      DataChunk::ErrorDataChunk,
      "Failed to read data from file: ", filePath,
      ", because chunk index is larger than chunk count in file.",
      " Chunk count in file:", std::to_string(chunkCountInFile),
      " Chunk index:", std::to_string(chunkIndex));

  std::vector<BYTE> data(DataChunk::CHUNK_BYTE_SIZE);
  const size_t chunkStartPos = chunkIndex * DataChunk::CHUNK_BYTE_SIZE;
  ERROR_RETURN_IF_FILE_OPERATION_FAILED(
      file.seekg(chunkStartPos),
      DataChunk::ErrorDataChunk,
      "Failed to seekg in file: ", filePath,
      ", on position: ", std::to_string(chunkStartPos));

  ERROR_RETURN_IF_FILE_OPERATION_FAILED(
      file.read(reinterpret_cast<char *>(data.data()), DataChunk::CHUNK_BYTE_SIZE),
      DataChunk::ErrorDataChunk,
      "Failed to read from file: ", filePath,
      ", on position: ", std::to_string(chunkStartPos),
      ", chunk size:: ", std::to_string(DataChunk::CHUNK_BYTE_SIZE));

  return DataChunkFactory::get_DataChunk(data);
}