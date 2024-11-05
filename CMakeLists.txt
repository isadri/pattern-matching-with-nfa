cmake_minimum_required(VERSION 3.30)

project(match)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Expr.cpp src/Parser.cpp src/Re2NFA.cpp
src/State.cpp src/NFASim.cpp src/Match.cpp)

add_executable(match ${SOURCE_FILES})

target_include_directories(match PRIVATE include/)
add_compile_options(-Wall -Wextra -Werror)
