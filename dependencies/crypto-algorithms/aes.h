/*********************************************************************
 * Filename:   aes.h
 * Author:     Brad Conte (brad AT bradconte.com)
 * Copyright:
 * Disclaimer: This code is presented "as is" without any guarantees.
 * Details:    Defines the API for the corresponding AES implementation.
 *********************************************************************/

#ifndef AES_H
#define AES_H

#include <stddef.h>

namespace AES
{
#define AES_BLOCK_SIZE 16 // AES operates on 16 bytes at a time

  typedef unsigned char BYTE; // 8-bit byte
  typedef unsigned int WORD;  // 32-bit word, change to "long" for 16-bit machines

  ///////////////////
  // AES
  ///////////////////
  // Key setup must be done before any AES en/de-cryption functions can be used.
  void aes_key_setup(
      const BYTE key[], // The key, must be 128, 192, or 256 bits
      WORD w[],         // Output key schedule to be used later
      int keysize);     // Bit length of the key, 128, 192, or 256

  void aes_encrypt(
      const BYTE in[],  // 16 bytes of plaintext
      BYTE out[],       // 16 bytes of ciphertext
      const WORD key[], // From the key setup
      int keysize);     // Bit length of the key, 128, 192, or 256

  void aes_decrypt(
      const BYTE in[],  // 16 bytes of ciphertext
      BYTE out[],       // 16 bytes of plaintext
      const WORD key[], // From the key setup
      int keysize);     // Bit length of the key, 128, 192, or 256

  ///////////////////
  // AES - CTR
  ///////////////////
  void increment_iv(
      BYTE iv[],         // Must be a multiple of AES_BLOCK_SIZE
      int counter_size); // bytes of the IV used for counting (low end)

  void aes_encrypt_ctr(
      const BYTE in[],  // Plaintext
      size_t in_len,    // Any byte length
      BYTE out[],       // Ciphertext, same length as plaintext
      const WORD key[], // From the key setup
      int keysize,      // Bit length of the key, 128, 192, or 256
      const BYTE iv[]); // IV, must be AES_BLOCK_SIZE bytes long

  void aes_decrypt_ctr(
      const BYTE in[],  // Ciphertext
      size_t in_len,    // Any byte length
      BYTE out[],       // Plaintext, same length as ciphertext
      const WORD key[], // From the key setup
      int keysize,      // Bit length of the key, 128, 192, or 256
      const BYTE iv[]); // IV, must be AES_BLOCK_SIZE bytes long

  ///////////////////
  // Test functions
  ///////////////////
  int aes_test();
  int aes_ctr_test();
};
#endif // AES_H
