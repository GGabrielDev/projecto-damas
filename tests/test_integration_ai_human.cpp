#include "Board.h"
#include "RuleEngine.h"
#include "AIPlayer.h"
#include "Man.h"
#include "ConsoleGame.h"
#include <cassert>
#include <iostream>
#include <sstream>

void test_ai_response_after_human_move() {
    Board board;
    RuleEngine engine;
    AIPlayer ai(/*depth=*/1);

    board.clear();

    // Humano (blanco) mueve primero
    board.placePiece({5, 0}, new Man(Color::White));
    board.placePiece({2, 1}, new Man(Color::Black)); // IA debe mover esta

    Move humanMove({5, 0}, {4, 1}, false);
    assert(engine.isValidMove(board, humanMove));
    engine.applyMove(board, humanMove);

    Move aiMove = ai.chooseMove(board, engine);
    assert(engine.isValidMove(board, aiMove));
    std::cout << "[OK] test_ai_response_after_human_move\n";
}

void test_ai_vs_ai_runs_turn() {
    Board board;
    RuleEngine engine;
    AIPlayer whiteAI(1);
    AIPlayer blackAI(1);

    board.initialize();

    for (int i = 0; i < 4; ++i) {
        Move whiteMove = whiteAI.chooseMove(board, engine);
        assert(engine.isValidMove(board, whiteMove));
        engine.applyMove(board, whiteMove);

        Move blackMove = blackAI.chooseMove(board, engine);
        assert(engine.isValidMove(board, blackMove));
        engine.applyMove(board, blackMove);
    }

    std::cout << "[OK] test_ai_vs_ai_runs_turn\n";
}

void test_ai_handles_no_moves() {
    Board board;
    RuleEngine engine;
    AIPlayer ai(/*depth=*/1);

    board.clear();

    // Colocar una ficha negra bloqueada completamente
    board.placePiece({0, 0}, new Man(Color::Black));
    board.placePiece({1, 1}, new Man(Color::White)); // Bloquea diagonal
    board.placePiece({2, 2}, new Man(Color::White)); // Bloquea salto de captura

    GameResult result;
    bool over = engine.isGameOver(board, Color::Black, result);
    assert(over && "Se espera que el juego esté terminado para las negras");
    assert(result == GameResult::WinWhite && "La IA blanca debería ganar");

    std::cout << "[OK] test_ai_handles_no_moves\n";
}

void test_console_game_ai_integration_sanity() {
    Board board;
    RuleEngine rules;
    board.clear();

    board.placePiece({5, 0}, new Man(Color::White));
    board.placePiece({2, 1}, new Man(Color::Black));

    AIPlayer ai(1);
    Move aiMove = ai.chooseMove(board, rules);

    assert(rules.isValidMove(board, aiMove));
    std::cout << "[OK] test_console_game_ai_integration_sanity\n";
}

int main() {
    test_ai_response_after_human_move();
    test_ai_vs_ai_runs_turn();
    test_ai_handles_no_moves();
    test_console_game_ai_integration_sanity();
    return 0;
}
