#pragma once
#ifndef FILEACCESS
#define FILEACCESS

// -------------------------------------------------
// Dependencies
// -------------------------------------------------

#include <filesystem>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#elif linux
#include <unistd.h>
#include <limits.h>
#endif

#include <global/global.h>

// --------------------------------------------
// Declarations
// --------------------------------------------

class FileAccess
{
public:
  enum ErrorCode
  {
    OK = 0,
    FILE_NOT_EXIST = 1,
    FILE_FAILED_OPEN = 2,
    FILE_FAILED_WRITE = 3,
    FILE_FAILED_READ = 4,
    FILE_FAILED_SEEK = 5,
    FILE_INDEX_OVER_SIZE = 6
  };

private:
  enum OpenMode
  {
    READ = std::ios::binary,
    WRITE = std::ios::binary,
    APPEND = std::ios::app | std::ios::binary
  };
  FileAccess() {}

public:
  static bool delete_file(const std::string &filePath);
  static bool create_file(const std::string &filePath);
  static bool file_exist(const std::string &filePath);

  static bool delete_dir(const std::string &dirPath);
  static bool create_dir(const std::string &dirPath);
  static bool dir_exist(const std::string &dirPath);

  static ErrorCode append_bytes_to_file(
      const std::string &filePath,
      const std::vector<BYTE> &bytes);
  static ErrorCode read_bytes_from_file(
      const std::string &filePath,
      std::vector<BYTE> &bytesByRef,
      const std::uintmax_t fromIndex,
      const u64 byteCount);

  static std::uintmax_t get_byte_count_left_in_file(
      const std::string &filePath,
      const std::uintmax_t fromIndex);

  static std::uintmax_t get_file_size(const std::string &filePath);
  static std::string get_file_folder_path(const std::string &path);
  static std::string get_exe_folder_path();
};

#endif