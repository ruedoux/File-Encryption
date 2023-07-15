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
private:
  FileAccess() {}

public:
  static bool delete_file(const std::string &filePath);
  static bool create_file(const std::string &filePath);
  static bool file_exist(const std::string &filePath);

  static bool delete_dir(const std::string &dirPath);
  static bool create_dir(const std::string &dirPath);
  static bool dir_exist(const std::string &dirPath);

  static std::uintmax_t get_file_size(const std::string &filePath);
  static std::string get_file_folder_path(const std::string &path);
  static std::string get_exe_folder_path();
};

#endif