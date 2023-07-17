#include "encryption.h"

std::vector<BYTE> Encryption::encrypt(
    const std::vector<BYTE> &bytes,
    std::vector<BYTE> key,
    std::vector<BYTE> vi)
{
  key = get_stretched_key(key);
  vi = get_padded_bytes(vi, VI_BYTE_SIZE);

  std::vector<BYTE> cryptedBytes(bytes.size());

  i32 keySize = key.size() * 8;
  std::vector<u32> preparedKey(keySize);
  AES::aes_key_setup(&key[0], &preparedKey[0], keySize);

  AES::aes_encrypt_ctr(&bytes[0], bytes.size(), &cryptedBytes[0], &preparedKey[0], keySize, &vi[0]);

  return cryptedBytes;
}

std::vector<BYTE> Encryption::decrypt(
    const std::vector<BYTE> &cryptedBytes,
    std::vector<BYTE> key,
    std::vector<BYTE> vi)
{
  return encrypt(cryptedBytes, key, vi);
}

std::vector<BYTE> Encryption::get_random_bytes(u64 size)
{
  static std::random_device rd;
  std::uniform_int_distribution<BYTE> distribution(0, BYTE_MAX_VALUE);

  std::vector<BYTE> bytes;
  for (u64 i = 0; i < size; i++)
  {
    bytes.push_back(distribution(rd));
  }
  return bytes;
}

std::vector<BYTE> Encryption::get_hashed_key(std::vector<BYTE> key)
{
  key = get_padded_bytes(key, KEY_BYTE_SIZE);
  std::vector<BYTE> hashedKey(KEY_BYTE_SIZE);

  Sha256::SHA256_CTX sha;
  Sha256::sha256_init(&sha);
  Sha256::sha256_update(&sha, &key[0], KEY_BYTE_SIZE);
  Sha256::sha256_final(&sha, &hashedKey[0]);

  return hashedKey;
}

std::vector<BYTE> Encryption::get_stretched_key(std::vector<BYTE> key)
{
  key = get_padded_bytes(key, KEY_BYTE_SIZE);
  for (size_t i = 0; i < HASH_ROTATIONS; i++)
  {
    key = get_hashed_key(key);
  }
  return key;
}

std::vector<BYTE> Encryption::get_padded_bytes(
    const std::vector<BYTE> bytes,
    u64 maxSize)
{
  std::vector<BYTE> paddedBytes(maxSize);
  if (static_cast<u64>(bytes.size()) < maxSize)
  {
    maxSize = bytes.size();
  }

  for (u64 i = 0; i < maxSize; i++)
  {
    paddedBytes[i] = bytes[i];
  }
  return paddedBytes;
}