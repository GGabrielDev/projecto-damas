#include <cassert>
#include <iostream>
#include "Board.h"
#include "RuleEngine.h"
#include "Position.h"

int main() {
    Board b;
    b.initialize();
    RuleEngine rules;
    // simple valid
    Move validMove({2,1}, {3,0}, false);
    assert(rules.isValidMove(b, validMove));
    // invalid move
    Move invalidMove({2,1}, {4,3}, false);
    assert(!rules.isValidMove(b, invalidMove));
    std::cout << "[OK] RuleEngine isValidMove test passed.\n";
    return 0;
}
