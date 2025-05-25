#include "Man.h"
#include "Board.h"

Man::Man(Color color) : Piece(color, PieceType::Man) {}

std::vector<Move> Man::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    int dir = (color_ == Color::Black) ? 1 : -1;

    // Movimientos simples
    for (int dc : {-1, 1}) {
        Position to{from.row + dir, from.col + dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8) {
            if (board.isEmpty(to)) {
                moves.emplace_back(from, to, false);
            }
        }
    }

    // Capturas
    for (int dc : {-1, 1}) {
        Position over{from.row + dir, from.col + dc};
        Position to{from.row + 2 * dir, from.col + 2 * dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 &&
            board.getPiece(over) != nullptr &&
            board.getPiece(over)->color() != color_ &&
            board.isEmpty(to)) {
            moves.emplace_back(from, to, true);
        }
    }

    return moves;
}
