add_executable(TestBoard test_board.cpp)
add_executable(TestSimpleMoves test_simple_moves.cpp)

target_include_directories(TestBoard PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(TestSimpleMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(TestBoard PRIVATE core)
target_link_libraries(TestSimpleMoves PRIVATE core)

add_test(NAME SimpleMoves COMMAND TestSimpleMoves)
