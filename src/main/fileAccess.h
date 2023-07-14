#pragma once
#ifndef FILEACCESS
#define FILEACCESS

// -------------------------------------------------
// DEPENDENCIES
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

#include "global/global.h"

// --------------------------------------------
// DECLARATIONS
// --------------------------------------------

class FileAccess
{
private:
  FileAccess() {}

public:
  static bool delete_file(std::string &filePath);
  static bool create_file(std::string &filePath);
  static bool file_exist(std::string &filePath);

  static bool delete_dir(std::string &dirPath);
  static bool create_dir(std::string &dirPath);
  static bool dir_exist(std::string &dirPath);

  static std::uintmax_t get_file_size(std::string &filePath);
  static std::string get_file_folder_path(std::string &path);
  static std::string get_exe_folder_path();
};

#endif