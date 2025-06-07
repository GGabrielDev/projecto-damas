#include "Man.h"
#include "Board.h"
#include "Move.h"
#include <algorithm>  // <-- necesario para std::find
#include <vector>
#include <cmath>
#include <iostream>

void exploreCaptures(const Board& board, const Position& from, Color color,
                     std::vector<Position> stops, std::vector<Move>& captures);

Man::Man(Color color) : Piece(color, PieceType::Man) {}

char Man::type() const {
    return 'M';
}

std::vector<Move> Man::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    int dir = (color() == Color::White) ? -1 : 1;  // Blancas suben, negras bajan

    // Movimientos simples (no captura)
    for (int dc : {-1, 1}) {
        Position to{from.row + dir, from.col + dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 && board.isEmpty(to)) {
            moves.emplace_back(from, to, false);
        }
    }

    // Verifica si hay oponentes adyacentes para iniciar exploración de captura
    bool hasEnemyNearby = false;
    for (int dr : {-1, 1}) {
        for (int dc : {-1, 1}) {
            Position over{from.row + dr, from.col + dc};
            if (over.row >= 0 && over.row < 8 && over.col >= 0 && over.col < 8) {
                Piece* maybeEnemy = board.getPiece(over);
                if (maybeEnemy && maybeEnemy->color() != color()) {
                    hasEnemyNearby = true;
                    break;
                }
            }
        }
        if (hasEnemyNearby) break;
    }

    if (hasEnemyNearby) {
        std::vector<Position> startPath = { from };
        exploreCaptures(board, from, color(), startPath, moves);
    }

    return moves;
}

void exploreCaptures(const Board& board, const Position& from, Color color,
                     std::vector<Position> stops, std::vector<Move>& captures) {
    const int forward = (color == Color::White) ? -1 : 1;
    bool found = false;

    for (int dc : {-1, 1}) {
        int dr = forward;
        Position over{from.row + dr, from.col + dc};          // Posición del enemigo
        Position to{from.row + 2 * dr, from.col + 2 * dc};    // Destino tras el salto

        // Validaciones básicas de tablero
        if (to.row < 0 || to.row >= 8 || to.col < 0 || to.col >= 8 || !board.isEmpty(to))
            continue;

        Piece* middle = board.getPiece(over);

        std::cout << "[DEBUG] En captura: from=(" << from.row << "," << from.col
                  << ") over=(" << over.row << "," << over.col << ") to=(" << to.row << "," << to.col << ") ";

        if (!middle)
            std::cout << "- over está vacío\n";
        else if (middle->color() == color)
            std::cout << "- pieza del mismo color\n";
        else
            std::cout << "- posible captura\n";

        if (middle && middle->color() != color) {
            if (std::find(stops.begin(), stops.end(), to) != stops.end()) {
                std::cout << "[DEBUG] Ciclo detectado: salto a (" << to.row << "," << to.col << ") ya visitado\n";
                continue;
            }

            // Clona el tablero, aplica captura y sigue recursivamente
            Board next = board;
            next.removePiece(over);
            next.movePiece(from, to);

            std::vector<Position> newStops = stops;
            newStops.push_back(to);

            exploreCaptures(next, to, color, newStops, captures);
            found = true;
        }
    }

    // Si no se encontró captura nueva, registrar el movimiento
    if (!found && stops.size() > 1) {
        Move m(stops.front(), stops.back(), true);
        for (size_t i = 1; i < stops.size() - 1; ++i) {
            m.addIntermediate(stops[i]);
        }

        std::cout << "[DEBUG] Capture added with path: ";
        for (const auto& pos : m.path()) {
            std::cout << "(" << pos.row << "," << pos.col << ") ";
        }
        std::cout << std::endl;
        captures.push_back(m);
    }
}
