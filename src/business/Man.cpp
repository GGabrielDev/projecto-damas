#include "Man.h"
#include "Board.h"  // Necesario para usar Board::isEmpty

Man::Man(Color color) : Piece(color, PieceType::Man) {}

std::vector<Move> Man::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    int dir = (color_ == Color::Black) ? 1 : -1;

    // Movimientos simples (adelante)
    for (int dc : {-1, 1}) {
        Position to{from.row + dir, from.col + dc};
        if (isValidPosition(to) && board.isEmpty(to)) {
            moves.emplace_back(from, to, false);
        }
    }

    // Capturas (saltos)
    for (int dc : {-2, 2}) {
        Position to{from.row + 2 * dir, from.col + dc};
        Position over{from.row + dir, from.col + dc / 2};

        if (isValidPosition(to) && board.isEmpty(to) && 
            board.getPiece(over) && board.getPiece(over)->color() != color_) {
            moves.emplace_back(from, to, true);
        }
    }

    return moves;
}
