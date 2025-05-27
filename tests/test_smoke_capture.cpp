#include "Board.h"
#include "Man.h"
#include "RuleEngine.h"
#include <cassert>
#include <iostream>

int main() {
    Board board;
    board.clear();

    // Coloca piezas para un simple salto
    board.placePiece({2, 3}, new Man(Color::Black)); // pieza que va a saltar
    board.placePiece({3, 4}, new Man(Color::White)); // pieza a capturar

    std::cout << "[SMOKE] Setup completo\n";

    // Verifica validez de movimientos
    Piece* piece = board.getPiece({2, 3});
    assert(piece && piece->color() == Color::Black);
    auto moves = piece->validMoves(board, {2, 3});

    std::cout << "[SMOKE] Movimientos posibles: " << moves.size() << "\n";
    for (const auto& move : moves) {
        std::cout << "[SMOKE] Movimiento: ";
        for (const auto& pos : move.path())
            std::cout << "(" << pos.row << "," << pos.col << ") ";
        std::cout << " | Captura: " << move.isCapture() << "\n";
    }

    // Busca el movimiento de captura
    Move captureMove({0, 0}, {0, 0}, false);
    for (const auto& move : moves) {
        if (move.isCapture())
            captureMove = move;
    }

    std::cout << "[SMOKE] Aplicando movimiento de captura...\n";

    RuleEngine rules;
    rules.applyMove(board, captureMove);

    std::cout << "[SMOKE] Estado después de mover:\n";
    std::cout << "  (2,3): " << (board.getPiece({2, 3}) ? "ocupado" : "vacío") << "\n";
    std::cout << "  (3,4): " << (board.getPiece({3, 4}) ? "ocupado" : "vacío") << "\n";
    std::cout << "  (4,5): " << (board.getPiece({4, 5}) ? "ocupado" : "vacío") << "\n";

    return 0;
}
