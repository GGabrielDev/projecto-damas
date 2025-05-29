add_executable(TestBoard test_board.cpp)
target_include_directories(TestBoard PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestBoard PRIVATE core)
add_test(NAME BoardInit COMMAND TestBoard)

add_executable(TestSimpleMoves test_simple_moves.cpp)
target_include_directories(TestSimpleMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestSimpleMoves PRIVATE core)
add_test(NAME SimpleMoves COMMAND TestSimpleMoves)

add_executable(TestPromotion test_promotion.cpp)
target_include_directories(TestPromotion PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestPromotion PRIVATE core)
add_test(NAME Promotion COMMAND TestPromotion)

add_executable(TestRemoveEmpty test_remove_and_empty.cpp)
target_include_directories(TestRemoveEmpty PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestRemoveEmpty PRIVATE core)
add_test(NAME RemoveEmpty COMMAND TestRemoveEmpty)

add_executable(TestManMoves test_man_valid_moves.cpp)
target_include_directories(TestManMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestManMoves PRIVATE core)
add_test(NAME ManMoves COMMAND TestManMoves)

add_executable(TestKingMoves test_king_valid_moves.cpp)
target_include_directories(TestKingMoves PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestKingMoves PRIVATE core)
add_test(NAME KingMoves COMMAND TestKingMoves)

add_executable(TestRuleIsValid test_ruleengine_isvalid.cpp)
target_include_directories(TestRuleIsValid PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestRuleIsValid PRIVATE core)
add_test(NAME RuleIsValid COMMAND TestRuleIsValid)

add_executable(TestCaptures test_captures.cpp)
target_include_directories(TestCaptures PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestCaptures PRIVATE core)
add_test(NAME Captures COMMAND TestCaptures)

add_executable(TestMultiCapture test_multi_capture.cpp)
target_include_directories(TestMultiCapture PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestMultiCapture PRIVATE core)
add_test(NAME MultiCapture COMMAND TestMultiCapture)

add_executable(TestApplyMove test_apply_move.cpp)
target_include_directories(TestApplyMove PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestApplyMove core)
add_test(NAME ApplyMove COMMAND TestApplyMove)

add_executable(TestSmokeCapture test_smoke_capture.cpp)
target_include_directories(TestSmokeCapture PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestSmokeCapture core)
add_test(NAME SmokeCapture COMMAND TestSmokeCapture)

add_executable(TestGameOver test_game_over.cpp)
target_include_directories(TestGameOver PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestGameOver core)
add_test(NAME GameOver COMMAND TestGameOver)

add_executable(TestGameConsole test_game_console.cpp)
target_include_directories(TestGameConsole PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestGameConsole core)
add_test(NAME GameConsole COMMAND TestGameOver)
