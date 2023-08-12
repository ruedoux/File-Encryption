cmake_minimum_required(VERSION 3.18)

## ---------------------------
## Variables
## ---------------------------

set(ThisName "FileCrypt")
set(ThisApiLibraryName "${ThisName}ApiLib")
set(ThisCliLibraryName "${ThisName}CliLib")
set(EncryptionLibraryName "${ThisName}EncryptionLibraryName")

set(ThisApiUnitTestName "${ThisName}ApiUnitTests")
set(ThisCliUnitTestName "${ThisName}CliUnitTests")
set(ThisApiIntergrationTestName "${ThisName}ApiIntegrationTests")
set(ThisCliIntergrationTestName "${ThisName}CliIntegrationTests")

## ---------------------------
## Settings
## ---------------------------

project(${ThisName} C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE Release)

enable_testing()

add_subdirectory(dependencies/googletest)

## ---------------------------
## Dependency files
## ---------------------------

include_directories(
  "${CMAKE_SOURCE_DIR}/dependencies"
  "${CMAKE_SOURCE_DIR}/src/main"
)

file(GLOB AlgorithmsSource
  "${CMAKE_SOURCE_DIR}/dependencies/crypto-algorithms/*.cpp"
  "${CMAKE_SOURCE_DIR}/dependencies/crypto-algorithms/*.h"
)

## ---------------------------
## Source files
## ---------------------------

file(GLOB_RECURSE ApiSource
  "${CMAKE_SOURCE_DIR}/src/main/Api/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/main/Api/*.h"
)

file(GLOB_RECURSE CliSource
  "${CMAKE_SOURCE_DIR}/src/main/Cli/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/main/Cli/*.h"
)

## ---------------------------
## Test files
## ---------------------------

file(GLOB_RECURSE UnitTestApiSource
  "${CMAKE_SOURCE_DIR}/src/test/unit/Api/*.cpp"
)

file(GLOB_RECURSE UnitTestCliSource
  "${CMAKE_SOURCE_DIR}/src/test/unit/Cli/*.cpp"
)

file(GLOB_RECURSE IntegrationTestApiSource
  "${CMAKE_SOURCE_DIR}/src/test/integration/Api/*.cpp"
)

file(GLOB_RECURSE IntegrationTestCliSource
  "${CMAKE_SOURCE_DIR}/src/test/integration/Cli/*.cpp"
)
## ---------------------------
## Create static libs
## ---------------------------

add_library(${ThisApiLibraryName} STATIC ${ApiSource} ${AlgorithmsSource})
add_library(${ThisCliLibraryName} STATIC ${CliSource})
target_link_libraries(${ThisCliLibraryName} PRIVATE ${ThisApiLibraryName})

## ---------------------------
## Unit Tests
## ---------------------------

add_executable(${ThisApiUnitTestName} ${UnitTestApiSource})
add_executable(${ThisCliUnitTestName} ${UnitTestCliSource})

target_link_libraries(${ThisApiUnitTestName} PUBLIC gtest_main ${ThisApiLibraryName})
target_link_libraries(${ThisCliUnitTestName} PUBLIC gtest_main ${ThisCliLibraryName})

add_test(NAME ${ThisApiUnitTestName} COMMAND ${ThisApiUnitTestName})
add_test(NAME ${ThisCliUnitTestName} COMMAND ${ThisCliUnitTestName})

## ---------------------------
## Integration Tests
## ---------------------------

add_executable(${ThisApiIntergrationTestName} ${IntegrationTestApiSource})
add_executable(${ThisCliIntergrationTestName} ${IntegrationTestCliSource})

target_link_libraries(${ThisApiIntergrationTestName} PUBLIC gtest_main ${ThisApiLibraryName})
target_link_libraries(${ThisCliIntergrationTestName} PUBLIC gtest_main ${ThisCliLibraryName})

add_test(NAME ${ThisApiIntergrationTestName} COMMAND ${ThisApiIntergrationTestName})
add_test(NAME ${ThisCliIntergrationTestName} COMMAND ${ThisCliIntergrationTestName})

## ---------------------------
## Test Build
## ---------------------------

add_custom_target(RunTests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${ThisApiUnitTestName} ${ThisCliUnitTestName} ${ThisApiIntergrationTestName} ${ThisCliIntergrationTestName}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

## ---------------------------
## Main build
## ---------------------------

add_executable(${ThisName} "${CMAKE_SOURCE_DIR}/src/main.cpp")
target_link_libraries(${ThisName} PRIVATE ${ThisCliLibraryName})

add_dependencies(${ThisName} RunTests)
