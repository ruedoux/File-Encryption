#include <global/exceptionHandling.h>
#include <encryptionApi.h>

int main(int argc, char *argv[])
{
  ExceptionHandling::init();

  std::string exeFolder = FileAccess::get_exe_folder_path();
  EncryptionApi::encrypt_file(
      exeFolder + "/test.txt",
      exeFolder + "/encrypted.txt",
      std::vector<BYTE>({10,0,2,3,4,5,12,3}));

  EncryptionApi::decrypt_file(
      exeFolder + "/encrypted.txt",
      exeFolder + "/decrypted.txt",
      std::vector<BYTE>({10,0,2,3,4,5,12,3}));

  return 0;
}
