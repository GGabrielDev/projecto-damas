#include "AIPlayer.h"
#include "Board.h"
#include "RuleEngine.h"
#include "Move.h"
#include "Position.h"
#include "Piece.h"
#include <cassert>
#include <iostream>

void test_ai_choose_simple_move() {
    // 1) Tablero en posición inicial
    Board board;
    board.initialize();          
    RuleEngine engine;
    AIPlayer ai(/*depth=*/1);    

    // AI juega con Blancas (en la prueba asumimos Color::White).
    Move aiMove = ai.chooseMove(board, engine);

    // Recolectar movimientos posibles verdaderos
    auto simpleMoves = engine.generateAllSimple(board, Color::White);
    auto captures    = engine.generateAllCaptures(board, Color::White);

    bool found = false;
    for (const auto& m : captures) {
        if (m.from().row == aiMove.from().row &&
            m.from().col == aiMove.from().col &&
            m.to().row   == aiMove.to().row &&
            m.to().col   == aiMove.to().col) {
            found = true;
            break;
        }
    }
    if (!found) {
        for (const auto& m : simpleMoves) {
            if (m.from().row == aiMove.from().row &&
                m.from().col == aiMove.from().col &&
                m.to().row   == aiMove.to().row &&
                m.to().col   == aiMove.to().col) {
                found = true;
                break;
            }
        }
    }

    assert(found && "[AIPlayer] chooseMove devolvió movimiento inválido");
    std::cout << "[OK] test_ai_choose_simple_move\n";
}

int main() {
    test_ai_choose_simple_move();
    return 0;
}
