#include <cassert>
#include <iostream>
#include "Board.h"
#include "Position.h"

int main() {
    Board b;
    b.initialize();
    int countBlack = 0, countWhite = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 1) {
                if (!b.isEmpty({i, j})) {
                    if (b.getPiece({i, j})->color() == Color::Black) ++countBlack;
                    else ++countWhite;
                }
            }
        }
    }
    assert(countBlack == 12);
    assert(countWhite == 12);
    std::cout << "[OK] Test de inicializacion de Board completado.\n";
    return 0;
}
