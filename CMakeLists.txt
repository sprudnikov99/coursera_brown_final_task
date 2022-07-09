cmake_minimum_required(VERSION 3.21)
project(bus_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(bus_manager main.cpp bus_manager.h bus_manager.cpp cache.h cache.cpp)
