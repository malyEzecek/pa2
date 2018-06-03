cmake_minimum_required(VERSION 3.8)
project(editor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/View.h src/View.cpp src/Model.h src/Model.cpp src/Cell.h src/Bool.h src/Cell.cpp src/Bool.cpp src/Text.cpp src/Text.h src/Reference.h src/Reference.cpp src/Number.cpp src/Number.h src/Operator.cpp src/Operator.h src/Expression.cpp src/Expression.h)
add_executable(editor ${SOURCE_FILES} src/Command.h src/Command.cpp)

add_executable(ncurses ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "-lncurses")