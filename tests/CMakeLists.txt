# tests/CMakeLists.txt

# TestBoard
add_executable(TestBoard test_board.cpp)
target_include_directories(TestBoard PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestBoard PRIVATE core)
add_test(NAME BoardInit COMMAND TestBoard)

# TestSimpleMoves
add_executable(TestSimpleMoves test_simple_moves.cpp)
target_include_directories(TestSimpleMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestSimpleMoves PRIVATE core)
add_test(NAME SimpleMoves COMMAND TestSimpleMoves)

# TestPromotion
add_executable(TestPromotion test_promotion.cpp)
target_include_directories(TestPromotion PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestPromotion PRIVATE core)
add_test(NAME Promotion COMMAND TestPromotion)

# TestRemoveEmpty
add_executable(TestRemoveEmpty test_remove_and_empty.cpp)
target_include_directories(TestRemoveEmpty PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestRemoveEmpty PRIVATE core)
add_test(NAME RemoveEmpty COMMAND TestRemoveEmpty)

# TestManMoves
add_executable(TestManMoves test_man_valid_moves.cpp)
target_include_directories(TestManMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestManMoves PRIVATE core)
add_test(NAME ManMoves COMMAND TestManMoves)

# TestKingMoves
add_executable(TestKingMoves test_king_valid_moves.cpp)
target_include_directories(TestKingMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestKingMoves PRIVATE core)
add_test(NAME KingMoves COMMAND TestKingMoves)

# TestRuleIsValid
add_executable(TestRuleIsValid test_ruleengine_isvalid.cpp)
target_include_directories(TestRuleIsValid PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestRuleIsValid PRIVATE core)
add_test(NAME RuleIsValid COMMAND TestRuleIsValid)
