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

    // Colocamos una ficha negra en {2, 3} y una blanca en {3, 4}
    // La casilla {4, 5} está libre -> captura posible
    b.placePiece({2, 3}, new Man(Color::Black));
    b.placePiece({3, 4}, new Man(Color::White));

    auto captures = rules.generateAllCaptures(b, Color::Black);
    std::cout << "Black captures found: " << captures.size() << std::endl;

    assert(captures.size() == 1);
    assert(captures[0].isCapture());
    assert(captures[0].from().row == 2 && captures[0].from().col == 3);
    assert(captures[0].to().row == 4 && captures[0].to().col == 5);

    std::cout << "[OK] Single capture test passed.\n";
    return 0;
}
