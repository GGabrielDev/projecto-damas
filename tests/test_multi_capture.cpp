#include <cassert>
#include <iostream>
#include "Board.h"
#include "RuleEngine.h"
#include "Man.h"
#include "Position.h"

int main() {
    Board b;
    RuleEngine rules;
    b.clear();

    // Escenario:
    // Black Man en {2, 3}
    // White en {3, 4} y {5, 6}
    // {4, 5} y {6, 7} están vacías
    b.placePiece({2, 3}, new Man(Color::Black));
    b.placePiece({3, 4}, new Man(Color::White));
    b.placePiece({5, 6}, new Man(Color::White));

    auto captures = rules.generateAllCaptures(b, Color::Black);
    std::cout << "Black captures found: " << captures.size() << std::endl;

    assert(!captures.empty());
    const auto& move = captures[0];
    assert(move.isCapture());
    assert(move.path().size() >= 3); // path: 2,3 -> 4,5 -> 6,7
    assert(move.from().row == 2 && move.from().col == 3);
    assert(move.to().row == 6 && move.to().col == 7);

    std::cout << "[OK] Multi-capture test passed.\n";
    return 0;
}
