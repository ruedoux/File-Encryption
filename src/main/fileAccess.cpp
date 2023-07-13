#include "fileAccess.h"

bool FileAccess::file_delete(std::string &filePath)
{
  return std::filesystem::remove(filePath);
}

bool FileAccess::file_create(std::string &filePath)
{
  std::fstream file(filePath, std::fstream::in | std::fstream::out | std::fstream::trunc);
  return file.is_open();
}

bool FileAccess::file_exist(std::string &filePath)
{
  return std::filesystem::is_regular_file(filePath);
}

bool FileAccess::dir_exist(std::string &dirPath)
{
  return std::filesystem::is_directory(dirPath);
}

std::uintmax_t FileAccess::get_file_size(std::string &filePath)
{
  return std::filesystem::file_size(filePath);
}

std::string FileAccess::get_file_folder_path(std::string &filePath)
{
  std::filesystem::path path(filePath);
  return path.parent_path().string();
}

std::string FileAccess::get_exe_folder_path()
{
#ifdef _WIN32
  char selfdirc[MAX_PATH] = {0};
  GetModuleFileNameA(NULL, selfdirc, MAX_PATH);
#else
  char selfdirc[PATH_MAX];
  ssize_t len = ::readlink("/proc/self/exe", selfdirc, sizeof(selfdirc) - 1);
  selfdirc[len] = '\0';
#endif
  std::string exeFilePath(selfdirc);
  std::string exeFolderPath = get_file_folder_path(exeFilePath);

  return exeFolderPath;
}

bool FileAccess::dir_create(std::string &dirPath)
{
  if (dir_exist(dirPath))
  {
    return true;
  }

  return std::filesystem::create_directory(dirPath);
}