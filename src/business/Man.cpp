#include "Man.h"
#include "Board.h"
#include "Move.h"
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
    int dir = (color() == Color::White) ? -1 : 1;

    // Movimiento simple
    for (int dc : {-1, 1}) {
        Position to{from.row + dir, from.col + dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 && board.isEmpty(to)) {
            moves.emplace_back(from, to, false);
        }
    }

    // Exploración de captura (solo si hay posibles oponentes adyacentes)
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
    static const int dirs[2] = {-1, 1};
    bool found = false;

    for (int dr : dirs) {
        for (int dc : dirs) {
            Position over{from.row + dr, from.col + dc};
            Position to{from.row + 2 * dr, from.col + 2 * dc};

            if (to.row < 0 || to.row >= 8 || to.col < 0 || to.col >= 8 || !board.isEmpty(to))
                continue;

            Piece* middle = board.getPiece(over);

            std::cout << "[DEBUG] En captura: from=(" << from.row << "," << from.col << ") over=(" 
                      << over.row << "," << over.col << ") to=(" << to.row << "," << to.col << ") ";

            if (!middle)
                std::cout << "- over está vacío\n";
            else if (middle->color() == color)
                std::cout << "- pieza del mismo color\n";
            else
                std::cout << "- posible captura\n";

            if (middle && middle->color() != color) {
                // Verificar que 'to' no está ya en stops (evitar bucles)
                bool already = false;
                for (auto& s : stops) {
                    if (s.row == to.row && s.col == to.col) {
                        already = true;
                        break;
                    }
                }
                if (already) continue;

                Board next = board;
                next.removePiece(over);
                next.movePiece(from, to);

                std::vector<Position> newStops = stops;
                newStops.push_back(to);

                exploreCaptures(next, to, color, newStops, captures);
                found = true;
            }
        }
    }

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
