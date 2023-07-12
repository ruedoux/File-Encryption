#include "fileAccess.h"

bool FileManager::file_delete(std::string &filePath)
{
  i32 result = remove(filePath.c_str());
  return result == 0;
}

bool FileManager::file_create(std::string &filePath)
{
  std::fstream file(filePath, std::fstream::in | std::fstream::out | std::fstream::trunc);
  return file.is_open();
}

bool FileManager::file_exist(std::string &filePath)
{
  std::ifstream file(filePath);
  return file.good();
}

bool FileManager::dir_exist(std::string &dirPath)
{
  struct stat info;
  if (stat(dirPath.c_str(), &info) != 0)
    return false;
  return info.st_mode & S_IFDIR;
}

std::streampos FileManager::get_file_size(std::string &filePath)
{
  std::fstream file(filePath, std::ifstream::ate | std::ifstream::binary);
  return file.tellg();
}

std::string FileManager::get_file_folder_path(std::string &filePath)
{
  if (dir_exist(filePath))
  {
    return filePath;
  }

  i32 count = 0;
  for (size_t i = 0; i < filePath.size(); i++)
  {
    count++;
    if (filePath[i] == '\\' || filePath[i] == '/')
    {
      count = 0;
    }
  }

  filePath = filePath.substr(0, filePath.size() - count);
  return filePath;
}

std::string FileManager::get_exe_folder_path()
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

bool FileManager::dir_create(std::string &dirPath)
{
  return makeDir(dirPath.c_str());
}