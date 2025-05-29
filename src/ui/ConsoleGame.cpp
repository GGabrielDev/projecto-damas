#include "ConsoleGame.h"
#include "Position.h"
#include <iostream>

ConsoleGame::ConsoleGame()
    : currentTurn_(Color::White) {
    board_.initialize();
}

void ConsoleGame::run() {
    std::cout << "=== Juego de Damas - Modo Consola ===\n";
    printBoard();

    while (true) {
        std::cout << "\nTurno de: " << (currentTurn_ == Color::White ? "Blancas" : "Negras") << "\n";
        std::cout << "[DEBUG] La lógica de selección de movimientos aún no está implementada.\n";

        // Aquí normalmente se seleccionaría y aplicaría un movimiento
        std::cout << "[INFO] Simulación terminada. Implementación pendiente.\n";
        break;
    }

    std::cout << "Juego finalizado.\n";
}

void ConsoleGame::switchTurn() {
    currentTurn_ = (currentTurn_ == Color::White) ? Color::Black : Color::White;
}

void ConsoleGame::printBoard() const {
    std::cout << "    0 1 2 3 4 5 6 7\n";
    std::cout << "   ----------------\n";
    for (int row = 0; row < 8; ++row) {
        std::cout << " " << row << " |";
        for (int col = 0; col < 8; ++col) {
            const Piece* p = board_.getPiece({row, col});
            if (!p) {
                std::cout << " .";
            } else {
                char symbol = (p->type() == PieceType::Man) ? 'm' : 'k';
                symbol = (p->color() == Color::White) ? toupper(symbol) : symbol;
                std::cout << " " << symbol;
            }
        }
        std::cout << "\n";
    }
}
