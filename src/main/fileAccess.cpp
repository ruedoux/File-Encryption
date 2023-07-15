#include "fileAccess.h"

bool FileAccess::delete_file(const std::string &filePath)
{
  return std::filesystem::remove(filePath);
}

bool FileAccess::create_file(const std::string &filePath)
{
  std::fstream file(filePath, std::fstream::in | std::fstream::out | std::fstream::trunc);
  return file.is_open();
}

bool FileAccess::file_exist(const std::string &filePath)
{
  return std::filesystem::is_regular_file(filePath);
}

bool FileAccess::delete_dir(const std::string &dirPath)
{
  return std::filesystem::remove_all(dirPath) > 0;
}

bool FileAccess::create_dir(const std::string &dirPath)
{
  if (dir_exist(dirPath))
  {
    return true;
  }

  return std::filesystem::create_directory(dirPath);
}

bool FileAccess::dir_exist(const std::string &dirPath)
{
  return std::filesystem::is_directory(dirPath);
}

std::uintmax_t FileAccess::get_file_size(const std::string &filePath)
{
  return std::filesystem::file_size(filePath);
}

std::string FileAccess::get_file_folder_path(const std::string &filePath)
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