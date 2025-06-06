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
    Board board;
    board.clear();

    board.placePiece({1,0}, new Man(Color::White));

    RuleEngine engine;
    AIPlayer ai(1);

    Move aiMove = ai.chooseMove(board, engine, Color::White);

    assert(!aiMove.isCapture());
    assert(aiMove.from().row == 1 && aiMove.from().col == 0);
    assert(aiMove.to().row == 0 && aiMove.to().col == 1);

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
