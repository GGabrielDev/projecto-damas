cmake_minimum_required(VERSION 3.10)
project(projecto-damas)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

include_directories(include)

add_executable(projecto-damas
    src/main.cpp
)

# Nuevo target: compilación de headers
add_executable(TestHeaders
    src/test_headers.cpp
)
