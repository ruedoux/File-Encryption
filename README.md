File-Encryption
=========

About
-----
Simple implementation of AES-CTR crypting using 256 bit hashed key. Hasihing is done using SHA-256. 

Encryption is done in 1MB blocks, IV is prepended in the clear for each block.


Building
-----------
Compilation requires: 
 - MinGw
 - cmake
 - Python 3

Compilation:
- Run `python build.py` command


Development
-----

**(!Currently project is WIP!)**

Project will only build after all unit tests pass. All testing is located in src/test directory. Library for doing the tests is [gtest](https://github.com/google/googletest).


