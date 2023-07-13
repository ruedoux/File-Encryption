cmake_minimum_required(VERSION 3.25)

## ---------------------------
## Variables
## ---------------------------

set(This "FC")
set(ThisLib "${This}Lib")
set(CryptoAlgorithmsLib "CryptoAlgorithmsLib")

set(ThisUT "UTests")
set(ThisIT "ITests")

## ---------------------------
## Settings
## ---------------------------

project(${This} C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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

file(GLOB UTSource
     "${CMAKE_SOURCE_DIR}/src/test/unit/*.cpp"
)

file(GLOB ITSource
     "${CMAKE_SOURCE_DIR}/src/test/integration/*.cpp"
)

## ---------------------------
## Create static libs
## ---------------------------

add_library(${ThisLib} STATIC ${MainSource})
add_library(${CryptoAlgorithmsLib} STATIC ${AlgorithmsSource})

## ---------------------------
## Tests
## ---------------------------

add_executable(${ThisUT} ${UTSource} ${AlgorithmsSource})
target_link_libraries(${ThisUT} PUBLIC gtest_main ${ThisLib})

add_test(NAME ${ThisUT} COMMAND ${ThisUT})

add_executable(${ThisIT} ${ITSource} ${AlgorithmsSource})
target_link_libraries(${ThisIT} PUBLIC gtest_main ${ThisLib})

add_test(NAME ${ThisIT} COMMAND ${ThisIT})

add_custom_target(RunTests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${ThisIT} ${ThisUT}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

## ---------------------------
## Main build
## ---------------------------

set(CMAKE_BUILD_TYPE Release)
add_executable(${This} "${CMAKE_SOURCE_DIR}/src/main.cpp")
target_link_libraries(${This} PRIVATE ${ThisLib} ${CryptoAlgorithmsLib})

add_dependencies(${This} RunTests)
