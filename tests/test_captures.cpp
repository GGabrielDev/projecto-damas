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
    std::cout << "Black captures found: " << captures.size() << std::endl;
    assert(captures.size() == 1);

    const Move& move = captures[0];
    std::cout << "Move path: ";
    for (const auto& pos : move.path()) {
        std::cout << "(" << pos.row << "," << pos.col << ") ";
    }
    std::cout << std::endl;

    rules.applyMove(board, move);

    std::cout << "After move applied:\n";
    std::cout << "From position (2,3): " << (board.getPiece({2, 3}) ? "occupied" : "empty") << std::endl;
    std::cout << "Middle position (3,4): " << (board.getPiece({3, 4}) ? "occupied" : "empty") << std::endl;
    std::cout << "To position (4,5): " << (board.getPiece({4, 5}) ? "occupied" : "empty") << std::endl;

    assert(board.getPiece({2, 3}) == nullptr); // original spot empty
    assert(board.getPiece({3, 4}) == nullptr); // captured piece gone
    assert(board.getPiece({4, 5}) != nullptr); // landed in final
    assert(board.getPiece({4, 5})->color() == Color::Black);

    std::cout << "[OK] Apply move test passed." << std::endl;
    return 0;
}
