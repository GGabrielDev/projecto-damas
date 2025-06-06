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
    Board board;
    board.clear();  

    board.placePiece({4,4}, new Man(Color::White));
    board.placePiece({3,3}, new Man(Color::Black));

    RuleEngine engine;
    AIPlayer ai(1);

    Move aiMove = ai.chooseMove(board, engine, Color::White);

    assert(aiMove.isCapture() && 
           aiMove.from().row == 4 && aiMove.from().col == 4 &&
           aiMove.to().row == 2 && aiMove.to().col == 2);
    std::cout << "[OK] test_ai_capture_priority\n";
}

int main() {
    test_ai_capture_priority();
    return 0;
}
