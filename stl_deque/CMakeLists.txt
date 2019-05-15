cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

project(stl_deque C CXX)

set(SRC_DEQUE main.cpp)

add_executable(stl_deque ${SRC_DEQUE})


