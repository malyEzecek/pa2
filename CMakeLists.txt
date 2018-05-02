cmake_minimum_required(VERSION 3.8)
project(editor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp View.h View.cpp Model.h Model.cpp Column.h Column.cpp)
add_executable(editor ${SOURCE_FILES})