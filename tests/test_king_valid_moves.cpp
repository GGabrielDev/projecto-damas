#include <cassert>
#include <iostream>
#include "Board.h"
#include "King.h"
#include "Position.h"

int main() {
    Board b;

    // Limpia completamente el tablero
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (!b.isEmpty({i, j}))
                b.removePiece({i, j});

    // Coloca un Rey blanco en el centro
    Position from{4, 4};
    b.placePiece(from, new King(Color::White));

    // Llama a validMoves sobre ese rey en el tablero limpio
    Piece* piece = b.getPiece(from);
    auto moves = piece->validMoves(b, from);

    // Debe haber 4 movimientos simples: (3,3), (3,5), (5,3), (5,5)
    assert(moves.size() == 4);
    std::cout << "[OK] King validMoves test passed.\n";
    return 0;
}
