cmake_minimum_required(VERSION 3.8)
project(editor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp View.h View.cpp Model.h Model.cpp Cell.h Bool.h Cell.cpp Bool.cpp Text.cpp Text.h Reference.h Reference.cpp Number.cpp Number.h Operator.cpp Operator.h Expression.cpp Expression.h)
add_executable(editor ${SOURCE_FILES} Command.h Command.cpp)

add_executable(ncurses ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "-lncurses")