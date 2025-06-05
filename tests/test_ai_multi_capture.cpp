#include "AIPlayer.h"
#include "Board.h"
#include "RuleEngine.h"
#include "Move.h"
#include "Position.h"
#include "Man.h"
#include "Piece.h"
#include <cassert>
#include <iostream>

void test_ai_multi_capture() {
    // 1) Tablero vacío
    Board board;
    board.clear();

    // 2) Colocar un Man blanco en (4,4).
    //    Fichas enemigas en (3,3) y en (1,1), con (2,2) y (0,0) libres:
    //    Debe permitir la cadena de captura: (4,4)->(2,2)->(0,0).
    board.placePiece({4,4}, new Man(Color::White));
    board.placePiece({3,3}, new Man(Color::Black));
    board.placePiece({1,1}, new Man(Color::Black));
    // (2,2) y (0,0) quedan vacías.

    RuleEngine engine;
    AIPlayer ai(/*depth=*/1);

    Move aiMove = ai.chooseMove(board, engine);
    // 1) Debe ser muestra captura
    assert(aiMove.isCapture() && "[AIPlayer] Se esperaba un movimiento de captura");

    const auto& path = aiMove.path();

    // 2) El origen debe ser (4,4):
    assert(path.front().row == 4 && path.front().col == 4);

    // 3) El destino final debe ser (0,0):
    assert(path.back().row == 0 && path.back().col == 0);

    // 4) Cada salto (pares consecutivos) debe estar en diagonal:
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        int dr = std::abs(path[i].row - path[i+1].row);
        int dc = std::abs(path[i].col - path[i+1].col);
        // Puede ser un salto de captura (2×2) o bien un “over” registrado (1×1):
        assert((dr == 2 && dc == 2) || (dr == 1 && dc == 1));
    }

    std::cout << "[OK] test_ai_multi_capture\n";
}

int main() {
    test_ai_multi_capture();
    return 0;
}
