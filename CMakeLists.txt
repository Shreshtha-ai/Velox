cmake_minimum_required(VERSION 3.16)

project(Velox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(velox
    src/main.cpp
    src/lexer.cpp
)

target_include_directories(velox PRIVATE include)