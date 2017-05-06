cmake_minimum_required(VERSION 2.8)
project(sstring)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(include)
#include_directories(src)
add_subdirectory(src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
