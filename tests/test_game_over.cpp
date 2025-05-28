#include "Board.h"
#include "GameResult.h"
#include "Man.h"
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

    // Pieza blanca bloqueada en la fila superior sin movimientos posibles
    board.placePiece({0, 1}, new Man(Color::White));

    // Oponente (Black) aún tiene piezas
    board.placePiece({7, 0}, new Man(Color::Black));
    board.placePiece({7, 2}, new Man(Color::Black));

    GameResult result;
    bool over = engine.isGameOver(board, Color::White, result);

    std::cout << "[TEST] Resultado isGameOver: " << std::boolalpha << over << "\n";
    std::cout << "[TEST] GameResult: " << static_cast<int>(result) << "\n";

    assert(over);
    assert(result == GameResult::WinBlack);
    std::cout << "[OK] Game over por no tener movimientos válidos\n";
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
