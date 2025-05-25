#include "King.h"
#include "Board.h"
#include "Position.h"

King::King(Color color) : Piece(color, PieceType::King) {}

std::vector<Move> King::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;

    // Direcciones diagonales (4 posibles)
    for (int dr : {-1, 1}) {
        for (int dc : {-1, 1}) {
            Position to{from.row + dr, from.col + dc}; // Solo 1 paso
            if (isValidPosition(to) && board.isEmpty(to)) {
                moves.emplace_back(from, to, false);
            }
        }
    }

    return moves;
}
