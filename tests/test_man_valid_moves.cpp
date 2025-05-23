#include <cassert>
#include <iostream>
#include "Board.h"
#include "Man.h"
#include "Position.h"

int main() {
    Board b;
    // clear board
    for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) if (!b.isEmpty({i,j})) b.removePiece({i,j});
    // place Man at {3,3}
    b.initialize(); b.removePiece({3,3});
    // manually allocate a Man
    b.removePiece({2,1});
    Man m(Color::Black);
    Position from{3,3};
    auto moves = m.validMoves(b, from);
    for (auto& mv : moves) {
        assert(mv.isCapture() == false);
        assert(abs(mv.to().row - from.row) == 1);
        assert(abs(mv.to().col - from.col) == 1);
    }
    std::cout << "[OK] Man validMoves test passed.\n";
    return 0;
}
