cmake_minimum_required(VERSION 3.30)

project(nfa)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/Expr.cpp src/Parser.cpp src/Re2Post.cpp
src/Re2NFA.cpp src/State.cpp src/NFASim.cpp)

add_executable(nfa ${SOURCE_FILES})

add_compile_options(-Wall -Wextra -Werror)
