#pragma once

#ifndef DECRYPTION_PRINT_FUNCTION
#define DECRYPTION_PRINT_FUNCTION

// --------------------------------------------
// Dependencies
// --------------------------------------------

#include <Api/encryptionApi.h>

#include "consoleFunction/consoleFunction.h"
#include "userInput.h"

// --------------------------------------------
// Declarations
// --------------------------------------------

class ConsoleDecryptionPrint : public ConsoleFunction
{
protected:
  static constexpr u64 MAXIMUM_PRINT_SIZE_BYTES = MiB(1);

  virtual void bound_function(const ArgumentConsumer &argumentConsumer) const override
  {
    const std::filesystem::path inputFilePath =
        argumentConsumer.get_required_argument("-i");
    const std::filesystem::path passwordFilePath =
        argumentConsumer.get_optional_argument("-fp");

    if (!FileAccess::file_exist(inputFilePath))
    {
      throw UserViewException("Input file doesnt exist: " + inputFilePath.string());
    }

    const std::uintmax_t inputFileSize = FileAccess::get_file_size(inputFilePath);
    if (inputFileSize > MAXIMUM_PRINT_SIZE_BYTES)
    {
      throw UserViewException("Input file too big to be printed! MaxSize: " + std::to_string(MAXIMUM_PRINT_SIZE_BYTES) + ", file size: " + std::to_string(inputFileSize));
    }

    Logger::log_warn("The output of the encrypted file will be printed into console.");
    Logger::log_warn("Make sure stdout is not logged anywhere on your system if you want to view sensitive data.");

    std::vector<BYTE> key;
    if (passwordFilePath.string().empty())
    {
      key = UserInput::get_input_from_console_hidden_as_bytes("Type key: ");
    }
    else if (FileAccess::file_exist(passwordFilePath))
    {
      FileAccess::read_bytes_from_file(
          passwordFilePath, key, 0, FileAccess::get_file_size(passwordFilePath));
    }
    else
    {
      throw UserViewException("Password file doesnt exist: " + passwordFilePath.string());
    }

    Logger::log("");
    Logger::log("-------START---------");
    print_decrypted_file_content_to_stdout(inputFilePath, key);
    Logger::log("--------END----------");
    Logger::log("");

    Logger::log_info("Press any key to clear the console output.");
    UserInput::get_char_from_console();
    UserInput::clear_console();
  }

  void print_decrypted_file_content_to_stdout(
      const std::filesystem::path &inputFilePath,
      const std::vector<BYTE> &key) const
  {
    THROW_EXCEPTION_IF_FILE_MISSING(inputFilePath);

    const u64 chunkSizeFrom = EncryptedDataChunk::get_desired_chunk_size();
    const uintmax_t fileSize = FileAccess::get_file_size(inputFilePath);
    const u64 maxChunks = Batching::get_chunk_count_in_file(inputFilePath, chunkSizeFrom);

    THROW_EXCEPTION_IF_TRUE(fileSize == 0);

    const u64 chunkCount = Batching::get_chunk_count_in_file(
        inputFilePath, EncryptedDataChunk::get_desired_chunk_size());
    for (u64 chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
    {
      const uintmax_t lastByteIndex = chunkSizeFrom * chunkIndex + chunkSizeFrom;

      const u64 bytesToRead =
          (lastByteIndex < fileSize) ? chunkSizeFrom : chunkSizeFrom - (lastByteIndex - fileSize);

      const EncryptedDataChunk encryptedChunk = Batching::read_chunk_from_file<EncryptedDataChunk>(
          inputFilePath, chunkIndex, bytesToRead);

      Logger::log(convert_byte_vector_to_string(ChunkEncryption::decrypt_chunk(encryptedChunk, key).get_data()));
    }
  }

  std::string convert_byte_vector_to_string(const std::vector<BYTE> &bytes) const
  {
    std::string output;
    for (size_t i = 0; i < bytes.size(); i++)
    {
      BYTE byte = bytes[i];
      if (byte > 126 || byte < 48)
      {
        byte = 48;
      }
      output.push_back(static_cast<char>(byte));
    }
    return output;
  }

public:
  ConsoleDecryptionPrint(const std::string &commandName)
      : ConsoleFunction(commandName)
  {
    add_description("Decrypts a given file and prints to console.");
    add_required_option("-i", "Input File path.");
    add_optional_option("-fp", "Path to file with password.");
  }
};

#endif