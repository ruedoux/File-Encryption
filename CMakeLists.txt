cmake_minimum_required(VERSION 3.25)

## ---------------------------
## Names
## ---------------------------

set(This "FC")
set(ThisTest "${This}Test")
set(ThisLib "${This}Lib")

set(CryptoAlgorithmsLib "${This}CryptoAlgorithmsLib")

## ---------------------------
## Settings
## ---------------------------

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(dependencies/googletest)

## ---------------------------
## Source files
## ---------------------------

include_directories(
     "${CMAKE_SOURCE_DIR}/dependencies"
     "${CMAKE_SOURCE_DIR}/src"
)

file(GLOB MainSource
     "${CMAKE_SOURCE_DIR}/src/main/*.cpp"
     "${CMAKE_SOURCE_DIR}/src/main/*.h"
)

file(GLOB AlgorithmsSource
     "${CMAKE_SOURCE_DIR}/dependencies/crypto-algorithms/*.cpp"
     "${CMAKE_SOURCE_DIR}/dependencies/crypto-algorithms/*.h"
)

file(GLOB TestSource
     "${CMAKE_SOURCE_DIR}/src/test/*.cpp"
)

## ---------------------------
## Create static libs
## ---------------------------

add_library(${ThisLib} STATIC ${MainSource})
add_library(${CryptoAlgorithmsLib} STATIC ${AlgorithmsSource})

## ---------------------------
## Build Test
## ---------------------------

add_executable(${ThisTest} ${TestSource} ${AlgorithmsSource})
target_link_libraries(${ThisTest} PUBLIC gtest_main ${ThisLib})

add_test(NAME ${ThisTest} COMMAND ${ThisTest})

add_custom_target(RunTests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${ThisTest}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

## ---------------------------
## Main build
## ---------------------------

set(CMAKE_BUILD_TYPE Release)
add_executable(${This} "${CMAKE_SOURCE_DIR}/src/main.cpp")
target_link_libraries(${This} PRIVATE ${ThisLib} ${CryptoAlgorithmsLib})

add_dependencies(${This} RunTests)
