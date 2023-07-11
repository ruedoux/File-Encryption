#include <gtest/gtest.h>
#include <main/encryption.h>

struct GlobalTest : public :: testing::Test
{
    virtual void SetUp() override {
        srand(time(NULL));
    }
    virtual void TearDown() override {}
};

TEST_F(GlobalTest, encrypt_bytes_and_decrypt_back) 
{
    std::vector<BYTE> bytes = Encryption::get_random_bytes(
        GLOBAL::get_random_number(1024, 2056)
    );
    std::vector<BYTE> key = Encryption::get_random_bytes(Encryption::KEY_LEN);
    std::vector<BYTE> vi = Encryption::get_random_bytes(Encryption::VI_LEN);
    
    std::vector<BYTE> encryptedBytes = Encryption::encrypt(bytes, key, vi);
    std::vector<BYTE> decryptedBytes = Encryption::decrypt(encryptedBytes, key, vi);

    ASSERT_EQ(bytes, decryptedBytes);
}
