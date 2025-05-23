#include <cassert>
#include <iostream>
#include "Board.h"
#include "King.h"
#include "Position.h"

int main() {
    Board b;
    // clear board
    for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) if (!b.isEmpty({i,j})) b.removePiece({i,j});
    King k(Color::White);
    Position from{4,4};
    auto moves = k.validMoves(b, from);
    assert(moves.size() == 4);
    std::cout << "[OK] King validMoves test passed.\n";
    return 0;
}
