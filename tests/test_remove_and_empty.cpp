#include <cassert>
#include <iostream>
#include "Board.h"
#include "Position.h"

int main() {
    Board b;
    b.initialize();
    Position pos{2,1};
    assert(!b.isEmpty(pos));
    b.removePiece(pos);
    assert(b.isEmpty(pos));
    assert(b.getPiece(pos) == nullptr);
    std::cout << "[OK] Remove and isEmpty test passed.\n";
    return 0;
}
