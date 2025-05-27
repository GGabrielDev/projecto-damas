#include "Board.h"
#include "RuleEngine.h"
#include "Man.h"
#include <cassert>
#include <iostream>

int main() {
    Board board;
    RuleEngine rules;

    board.clear();
    board.placePiece({2, 3}, new Man(Color::Black));
    board.placePiece({3, 4}, new Man(Color::White));

    auto captures = rules.generateAllCaptures(board, Color::Black);
    assert(captures.size() == 1);
    
    rules.applyMove(board, captures[0]);

    assert(board.getPiece({2, 3}) == nullptr); // original spot empty
    assert(board.getPiece({3, 4}) == nullptr); // captured piece gone
    assert(board.getPiece({4, 5}) != nullptr); // landed in final
    assert(board.getPiece({4, 5})->color() == Color::Black);

    std::cout << "[OK] Apply move test passed." << std::endl;
    return 0;
}
