#include "RuleEngine.h"
#include "Board.h"
#include "GameResult.h"
#include "Man.h"
#include "King.h"
#include <algorithm>
#include <iostream>

/// Determina si un movimiento es legal según las reglas del juego.
/// Si hay capturas disponibles, deben tomarse (prioridad sobre movimientos simples).
/// Complejidad: O(C + S) /	C = capturas posibles, S = movimientos simples (ambos acotados por constante)
bool RuleEngine::isValidMove(const Board& board, const Move& move) const {
    auto captures = generateAllCaptures(board, board.getPiece(move.from())->color());

    // Si hay capturas, el movimiento debe coincidir con una de ellas
    if (!captures.empty()) {
        return std::any_of(captures.begin(), captures.end(), [&](const Move& m) {
            return m.from() == move.from() && m.to() == move.to();
        });
    }

    // De lo contrario, validar si es un movimiento simple permitido
    auto simple = generateAllSimple(board, board.getPiece(move.from())->color());
    return std::any_of(simple.begin(), simple.end(), [&](const Move& m) {
        return m.from() == move.from() && m.to() == move.to();
    });
}

/// Genera todos los movimientos *simples* (sin captura) que puede realizar el jugador.
/// O(1) / 8x8 posiciones × máx 4 mov/pieza = 256 operaciones (constante)
std::vector<Move> RuleEngine::generateAllSimple(const Board& board, Color playerColor) const {
    std::vector<Move> moves;

    // Recorre el tablero buscando piezas del jugador
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position pos{r, c};
            Piece* p = board.getPiece(pos);

            if (p && p->color() == playerColor) {
                auto vm = p->validMoves(board, pos);
                for (const auto& move : vm) {
                    if (!move.isCapture()) {
                        moves.push_back(move);
                    }
                }
            }
        }
    }

    return moves;
}

/// Genera todos los movimientos de *captura* disponibles para el jugador.
/// O(1) / Mismo principio que generateAllSimple()
std::vector<Move> RuleEngine::generateAllCaptures(const Board& board, Color playerColor) const {
    std::vector<Move> captures;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position pos{r, c};
            Piece* p = board.getPiece(pos);

            if (p && p->color() == playerColor) {
                auto moves = p->validMoves(board, pos);
                for (const auto& move : moves) {
                    if (move.isCapture()) {
                        captures.push_back(move);
                    }
                }
            }
        }
    }

    return captures;
}

/// Aplica un movimiento sobre el tablero. Si es una captura, elimina las piezas saltadas.
/// O(P) / P = longitud del camino (máx 12 saltos en damas)
void RuleEngine::applyMove(Board& board, const Move& move) const {
    const auto& path = move.path();

    if (move.isCapture()) {
        // Capturas múltiples posibles: recorrer el camino completo
        for (size_t i = 0; i < path.size() - 1; ++i) {
            Position from = path[i];
            Position to   = path[i + 1];

            // Si es salto válido (2 posiciones), buscar la pieza en el medio
            if (std::abs(from.row - to.row) == 2 && std::abs(from.col - to.col) == 2) {
                Position mid{(from.row + to.row) / 2, (from.col + to.col) / 2};

                if (mid.row < 0 || mid.row >= 8 || mid.col < 0 || mid.col >= 8) {
                    std::cerr << "[ERROR] Mid position out of bounds: (" << mid.row << "," << mid.col << ")\n";
                    continue;
                }

                Piece* target = board.getPiece(mid);
                if (!target) {
                    std::cerr << "[ERROR] Tried to capture empty square at: (" << mid.row << "," << mid.col << ")\n";
                } else {
                    board.removePiece(mid);
                }
            }

            board.movePiece(from, to);
        }
    } else {
        // Movimiento simple
        board.movePiece(move.from(), move.to());
    }
}

/// Evalúa si el juego ha terminado para el jugador actual.
/// Devuelve true si se acabó, y asigna el resultado correspondiente.
/// O(1) / 8x8 chequeo + generación movimientos (operaciones constantes)
bool RuleEngine::isGameOver(const Board& board, Color currentPlayer, GameResult& result) const {
    // Verificar si el jugador tiene piezas restantes
    bool hasPieces = false;
    for (int r = 0; r < 8 && !hasPieces; ++r) {
        for (int c = 0; c < 8 && !hasPieces; ++c) {
            Piece* p = board.getPiece({r, c});
            if (p && p->color() == currentPlayer) {
                hasPieces = true;
            }
        }
    }

    // Si no tiene piezas, el oponente gana
    if (!hasPieces) {
        result = (currentPlayer == Color::White) ? GameResult::WinBlack : GameResult::WinWhite;
        std::cout << "[DEBUG] No hay piezas restantes\n";
        return true;
    }

    // Si tiene capturas, el juego continúa
    auto captures = generateAllCaptures(board, currentPlayer);
    if (!captures.empty()) {
        std::cout << "[DEBUG] Hay capturas válidas:\n";
        for (const auto& m : captures) {
            std::cout << "  Captura: ";
            for (const auto& p : m.path()) {
                std::cout << "(" << p.row << "," << p.col << ") ";
            }
            std::cout << "\n";
        }
        result = GameResult::Ongoing;
        return false;
    }

    // Si tiene movimientos simples, el juego también continúa
    auto simple = generateAllSimple(board, currentPlayer);
    if (!simple.empty()) {
        std::cout << "[DEBUG] Hay movimientos simples válidos:\n";
        for (const auto& m : simple) {
            std::cout << "  De (" << m.from().row << "," << m.from().col << ") a ("
                      << m.to().row << "," << m.to().col << ")\n";
        }
        result = GameResult::Ongoing;
        return false;
    }

    // Si no tiene capturas ni movimientos simples, pierde
    result = (currentPlayer == Color::White) ? GameResult::WinBlack : GameResult::WinWhite;
    std::cout << "[DEBUG] No hay movimientos válidos restantes\n";
    return true;
}
