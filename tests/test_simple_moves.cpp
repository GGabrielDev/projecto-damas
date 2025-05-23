#include <cassert>
#include <iostream>
#include "Board.h"
#include "RuleEngine.h"
#include "Position.h"

int main() {
    Board b;
    b.initialize();

    RuleEngine rules;
    auto blackMoves = rules.generateAllSimple(b, Color::Black);
    std::cout << "Black moves count: " << blackMoves.size() << std::endl;
    assert(blackMoves.size() == 7);

    auto whiteMoves = rules.generateAllSimple(b, Color::White);
    std::cout << "White moves count: " << whiteMoves.size() << std::endl;
    assert(whiteMoves.size() == 7);

    std::cout << "[OK] Simple moves test passed (" 
              << blackMoves.size() << " black, "
              << whiteMoves.size() << " white)." 
              << std::endl;
    return 0;
}
