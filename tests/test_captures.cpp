#include <cassert>
#include <iostream>
#include "Board.h"
#include "RuleEngine.h"
#include "Man.h"

int main() {
    Board b;
    RuleEngine rules;
    b.clear();

    // Negro en posición (2, 3), Blanco en (3, 4), debe capturar hacia (4, 5)
    b.placePiece({2, 3}, new Man(Color::Black));
    b.placePiece({3, 4}, new Man(Color::White));

    auto captures = rules.generateAllCaptures(b, Color::Black);
    assert(captures.size() == 1);
    assert(captures[0].from().row == 2 && captures[0].from().col == 3);
    assert(captures[0].to().row == 4 && captures[0].to().col == 5);
    assert(captures[0].isCapture());

    std::cout << "[OK] Basic capture test passed.\n";
    return 0;
}
