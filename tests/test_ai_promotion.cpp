#include "AIPlayer.h"
#include "Board.h"
#include "King.h"
#include "Man.h"
#include "Move.h"
#include "Position.h"
#include "Piece.h"
#include "RuleEngine.h"
#include <cassert>
#include <iostream>

void test_ai_promotion_simple() {
    // 1) Tablero vacío
    Board board;
    board.clear();

    // 2) Colocar un Man blanco en (1,0). No hay capturas posibles.
    board.placePiece({1,0}, new Man(Color::White));
    // (0,1) está vacía: la promoción simple es (1,0)->(0,1).

    RuleEngine engine;
    AIPlayer ai(/*depth=*/1);

    // IA elige un movimiento legal; no hay capturas, así que escogerá (1,0)->(0,1).
    Move aiMove = ai.chooseMove(board, engine);

    // Verificar que sea un movimiento simple y que llegue a la última fila (row=0).
    assert(!aiMove.isCapture());
    assert(aiMove.from().row == 1 && aiMove.from().col == 0);
    assert(aiMove.to().row == 0 && aiMove.to().col == 1);

    // Aplicar el movimiento y confirmar que la ficha se convierte en King
    engine.applyMove(board, aiMove);
    Piece* p = board.getPiece({0,1});
    assert(p != nullptr);
    assert(p->type() == PieceType::King);

    std::cout << "[OK] test_ai_promotion_simple\n";
}

int main() {
    test_ai_promotion_simple();
    return 0;
}
