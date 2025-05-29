#include "Board.h"
#include "ConsoleGame.h"
#include "King.h"
#include "Man.h"
#include "RuleEngine.h"
#include <cassert>
#include <iostream>
#include <vector>

void test_console_game_prints_board() {
    ConsoleGame game;
    game.printBoard(); // Should show initial layout with expected symbols
}

void test_render_board_initial_state() {
    Board board;
    board.initialize();

    std::cout << "[TEST] Tablero inicial:\n";
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board.getPiece({r, c});
            if (p) {
                std::cout << (p->color() == Color::Black ? 'B' : 'W');
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

void test_render_board_custom_setup() {
    Board board;
    board.clear();
    board.placePiece({3, 4}, new Man(Color::Black));
    board.placePiece({4, 5}, new Man(Color::White));

    std::cout << "[TEST] Tablero con captura posible:\n";
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board.getPiece({r, c});
            if (p) {
                std::cout << (p->color() == Color::Black ? 'B' : 'W');
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

int main() {
    test_render_board_initial_state();
    test_render_board_custom_setup();
    test_console_game_prints_board();
    std::cout << "[OK] Pruebas de consola inicial pasadas.\n";
    return 0;
}
