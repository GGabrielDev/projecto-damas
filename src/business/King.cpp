#include "King.h"
#include "Board.h"  // Necesario para usar Board::isEmpty

King::King(Color color) : Piece(color, PieceType::King) {}

std::vector<Move> King::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    // Puede moverse diagonalmente en 4 direcciones
    for (int dr : {-1, 1}) {
        for (int dc : {-1, 1}) {
            Position to{from.row + dr, from.col + dc};
            if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8) {
                if (board.isEmpty(to)) {
                    moves.emplace_back(from, to, false);
                }
            }
        }
    }
    return moves;
}
