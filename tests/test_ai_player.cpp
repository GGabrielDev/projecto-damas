#include "AIPlayer.h"
#include "Board.h"
#include "RuleEngine.h"
#include "Move.h"
#include "Position.h"
#include "Piece.h"
#include <cassert>
#include <iostream>

void test_ai_choose_simple_move() {
    Board board;
    board.initialize();          
    RuleEngine engine;
    AIPlayer ai(1);    

    Move aiMove = ai.chooseMove(board, engine, Color::White);

    auto simpleMoves = engine.generateAllSimple(board, Color::White);
    auto captures    = engine.generateAllCaptures(board, Color::White);

    bool found = false;
    for (const auto& m : captures) {
        if (m.from() == aiMove.from() && m.to() == aiMove.to()) {
            found = true;
            break;
        }
    }
    if (!found) {
        for (const auto& m : simpleMoves) {
            if (m.from() == aiMove.from() && m.to() == aiMove.to()) {
                found = true;
                break;
            }
        }
    }

    assert(found);
    std::cout << "[OK] test_ai_choose_simple_move\n";
}

int main() {
    test_ai_choose_simple_move();
    return 0;
}
