cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

project(share_ptr C CXX)

set(SRC_LIST main.cpp)

message("PROJECT_SOURCE_DIR points to " ${SRC_LIST})

add_executable(share_ptr ${SRC_LIST})   



