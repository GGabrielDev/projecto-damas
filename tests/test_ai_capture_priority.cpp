#include "AIPlayer.h"
#include "Board.h"
#include "RuleEngine.h"
#include "Man.h"
#include "Move.h"
#include "Position.h"
#include "Piece.h"
#include <cassert>
#include <iostream>

void test_ai_capture_priority() {
    // 1) Tablero vacío
    Board board;
    board.clear();  

    // 2) Colocar una ficha blanca en (4,4) y una negra en (3,3),
    //    con (2,2) libre para la captura.
    board.placePiece({4,4}, new Man(Color::White));
    board.placePiece({3,3}, new Man(Color::Black));
    // Posición (2,2) queda vacía por defecto.

    RuleEngine engine;
    AIPlayer ai(1);  // Profundidad 1

    // IA juega con blancas → debe capturar de (4,4) a (2,2).
    Move aiMove = ai.chooseMove(board, engine);

    // Verificar que sea captura y que termine en (2,2).
    assert(aiMove.isCapture() && 
           aiMove.from().row == 4 && aiMove.from().col == 4 &&
           aiMove.to().row == 2 && aiMove.to().col == 2);
    std::cout << "[OK] test_ai_capture_priority\n";
}

int main() {
    test_ai_capture_priority();
    return 0;
}

