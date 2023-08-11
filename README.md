File-Encryption
=========

About
-----
Simple implementation of AES-CTR encryption using 256 bit hashed key. Hasihing is done using SHA-256 with stretching. 

Encryption is done in 1MB blocks, IV is prepended in the clear for each block.

Program is made with intention of being CLI integrated, all commands and their options can be listed using `help` command.

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
Project has built in CI/CD with gtest and cmake so it wont compile unless all tests pass (`src/test` folder) to ensure the program works as expected.



