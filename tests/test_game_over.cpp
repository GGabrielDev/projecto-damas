#include "Board.h"
#include "RuleEngine.h"
#include <iostream>
#include <cassert>

void test_no_pieces_left() {
    Board board;
    RuleEngine engine;
    board.clear();
    board.placePiece({0, 1}, new Man(Color::White));

    GameResult result;
    bool over = engine.isGameOver(board, Color::Black, result);
    assert(over);
    assert(result == GameResult::WinWhite);
    std::cout << "[OK] Win by no pieces left\n";
}

void test_no_valid_moves() {
    Board board;
    RuleEngine engine;
    board.clear();
    board.placePiece({0, 1}, new Man(Color::White));
    board.placePiece({1, 2}, new Man(Color::Black)); // blocked by edge and ally

    GameResult result;
    bool over = engine.isGameOver(board, Color::Black, result);
    assert(over);
    assert(result == GameResult::WinWhite);
    std::cout << "[OK] Win by no valid moves\n";
}

void test_not_over_yet() {
    Board board;
    RuleEngine engine;
    board.clear();
    board.placePiece({2, 3}, new Man(Color::Black));
    board.placePiece({5, 2}, new Man(Color::White));

    GameResult result;
    bool over = engine.isGameOver(board, Color::White, result);
    assert(!over);
    assert(result == GameResult::Ongoing);
    std::cout << "[OK] Game not over\n";
}

int main() {
    test_no_pieces_left();
    test_no_valid_moves();
    test_not_over_yet();
    return 0;
}
