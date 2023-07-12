#pragma once
#ifndef FILEACCESS
#define FILEACCESS

// -------------------------------------------------
// DEPENDENCIES
// -------------------------------------------------

#include<limits>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#elif linux
#include <unistd.h>
#include <limits.h>
#endif

#include "global.h"

// -------------------------------------------------
// MACROS
// -------------------------------------------------

#ifdef _WIN32
#define makeDir(path) _mkdir(path);
#define DEFAULT_PATH_SEPARATOR "\\"
#elif linux
#define makeDir(path) mkdir(path, 0777);
#define DEFAULT_PATH_SEPARATOR "/"
#endif

// --------------------------------------------
// DECLARATIONS
// --------------------------------------------

class FileManager
{
private:
  FileManager() {}

public:
  static bool file_delete(std::string &filePath);
  static bool file_create(std::string &filePath);
  static bool dir_create(std::string &dirPath);
  static bool file_exist(std::string &filePath);
  static bool dir_exist(std::string &dirPath);
  static std::streampos get_file_size(std::string &filePath);
  static std::string get_file_folder_path(std::string &path);
  static std::string get_exe_folder_path();
};

#endif