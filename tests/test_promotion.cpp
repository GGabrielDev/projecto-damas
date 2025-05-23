// tests/test_promotion.cpp
#include <cassert>
#include <iostream>
#include "Board.h"
#include "Position.h"
#include "Man.h"
#include "Piece.h"

int main() {
    Board b;
    // Colocamos manualmente un Man negro en fila 6, col 1
    b.clear();
    b.placePiece({6, 1}, new Man(Color::Black));
    // Movemos para coronar
    b.movePiece({6, 1}, {7, 0});
    Piece* p = b.getPiece({7, 0});
    assert(p != nullptr);
    assert(p->type() == PieceType::King);
    std::cout << "[OK] Promotion test passed.\n";
    return 0;
}
