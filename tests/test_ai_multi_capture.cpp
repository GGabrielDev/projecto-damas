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
    Board board;
    board.clear();

    board.placePiece({4,4}, new Man(Color::White));
    board.placePiece({3,3}, new Man(Color::Black));
    board.placePiece({1,1}, new Man(Color::Black));

    RuleEngine engine;
    AIPlayer ai(1);

    Move aiMove = ai.chooseMove(board, engine, Color::White);
    assert(aiMove.isCapture());

    const auto& path = aiMove.path();
    assert(path.front().row == 4 && path.front().col == 4);
    assert(path.back().row == 0 && path.back().col == 0);

    for (size_t i = 0; i + 1 < path.size(); ++i) {
        int dr = std::abs(path[i].row - path[i+1].row);
        int dc = std::abs(path[i].col - path[i+1].col);
        assert((dr == 2 && dc == 2) || (dr == 1 && dc == 1));
    }

    std::cout << "[OK] test_ai_multi_capture\n";
}

int main() {
    test_ai_multi_capture();
    return 0;
}
