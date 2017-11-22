cmake_minimum_required(VERSION 3.8)
project(topsis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/MyFileReader.cpp src/MyFileReader.h src/Topsis.cpp src/Topsis.h)
add_executable(topsis ${SOURCE_FILES})