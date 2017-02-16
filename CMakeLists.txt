cmake_minimum_required(VERSION 2.8)
project(sstring)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
add_subdirectory(src)
