cmake_minimum_required(VERSION 3.0)
project(Forca VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -pedantic -Wall -Wextra -Werror -Wno-unused -pthread")

set(APP_NAME "MatrixMultiplication")
include_directories(include)
add_executable(${APP_NAME}
    src/main.cpp
    src/Matrix.cpp
    src/Sequencial.cpp)