#include <global/exceptionHandling.h>
#include <encryptionInterface.h>

int main(int argc, char *argv[])
{
  ExceptionHandling::init();

  std::string exeFolder = FileAccess::get_exe_folder_path();
  EncryptionInterface::process_file(
      EncryptionInterface::ENCRYPT_BIND,
      exeFolder + "/test.txt",
      exeFolder + "/encrypted.txt",
      std::vector<BYTE>({10,0,2,3,4,5,12,3}));

  //EncryptionInterface::process_file(
  //    EncryptionInterface::DECRYPT_BIND,
  //    exeFolder + "/encrypted.txt",
  //    exeFolder + "/decrypted.txt",
  //    std::vector<BYTE>({10,0,2,3,4,5,12,3}));

  return 0;
}
