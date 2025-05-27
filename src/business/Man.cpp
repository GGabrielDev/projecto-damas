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

    // Simple moves
    for (int dc : {-1, 1}) {
        Position to{from.row + dir, from.col + dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 && board.isEmpty(to)) {
            moves.emplace_back(from, to, false);
        }
    }

    // Captures (recursive)
    std::vector<Position> startPath = { from };
    exploreCaptures(board, from, color(), startPath, moves);

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
            if (middle && middle->color() != color) {
                Board next = board;
                next.removePiece(over);
// src/business/Man.cpp
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
