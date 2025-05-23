#include "Man.h"
#include "Board.h"  // Necesario para usar Board::isEmpty

Man::Man(Color color) : Piece(color, PieceType::Man) {}

std::vector<Move> Man::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    int dir = (color_ == Color::Black) ? 1 : -1;
    // Diagonales simples
    for (int dc : {-1, 1}) {
        Position to{from.row + dir, from.col + dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8) {
            if (board.isEmpty(to)) {
                moves.emplace_back(from, to, false);
            }
        }
    }
    return moves;
}
