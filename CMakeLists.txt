cmake_minimum_required(VERSION 3.10)
project(projecto-damas)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

# Librería core del negocio
add_library(core
    src/business/Board.cpp
    src/business/Piece.cpp
    src/business/Man.cpp
    src/business/King.cpp
    src/business/Move.cpp
)
target_include_directories(core PUBLIC include)

# Ejecutable principal
add_executable(projecto-damas
    src/main.cpp
)
target_link_libraries(projecto-damas core)

# TestHeaders (smoke-test)
add_executable(TestHeaders
    src/test_headers.cpp
)
target_link_libraries(TestHeaders core)

# Directorio de tests
enable_testing()
add_subdirectory(tests)
