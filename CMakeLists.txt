cmake_minimum_required(VERSION 3.10)
project(projecto-damas)

set(CMAKE_CXX_STANDARD 17)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Librería core del negocio
add_library(core
    src/business/AIPlayer.cpp
    src/business/Board.cpp
    src/business/GameResult.cpp
    src/business/King.cpp
    src/business/Man.cpp
    src/business/Move.cpp
    src/business/Piece.cpp
    src/business/RuleEngine.cpp
    src/file/FileManager.cpp
    src/ui/ConsoleGame.cpp
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
