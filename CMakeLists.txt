cmake_minimum_required(VERSION 3.9)
project(Slt)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/Test/tankTest)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11 -g -Wall -Wno-unused-variable -pthread")

set(CMAKE_VERBOSE_MAKEFILE ON)
