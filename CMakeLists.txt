cmake_minimum_required(VERSION 3.8)
project(editor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp View/View.h View/View.cpp Model/Model.h Model/Model.cpp Model/Cell.h Model/Bool.h Model/Cell.cpp Model/Bool.cpp Model/Text.cpp Model/Text.h Model/Reference.h Model/Reference.cpp Model/Number.cpp Model/Number.h Model/Operator.cpp Model/Operator.h Model/Expression.cpp Model/Expression.h)
add_executable(editor ${SOURCE_FILES} Controller/Command.h Controller/Command.cpp)

add_executable(ncurses ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "-lncurses")