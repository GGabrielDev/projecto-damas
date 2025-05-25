#include "Man.h"
#include "Board.h"
#include "Move.h"

Man::Man(Color color) : Piece(color, PieceType::Man) {}

static void exploreCaptures(const Board& board, const Position& from, Color color,
                             std::vector<Position> path, std::vector<Move>& captures) {
    bool extended = false;
    int dir = (color == Color::Black) ? 1 : -1;

    for (int dc : {-1, 1}) {
        Position over{from.row + dir, from.col + dc};
        Position to{from.row + 2 * dir, from.col + 2 * dc};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 &&
            board.getPiece(over) != nullptr &&
            board.getPiece(over)->color() != color &&
            board.isEmpty(to)) {

            Board next = board;
            next.removePiece(over);
            next.movePiece(from, to);
            std::vector<Position> nextPath = path;
            nextPath.push_back(to);
            exploreCaptures(next, to, color, nextPath, captures);
            extended = true;
        }
    }

    if (!extended && path.size() > 1) {
        Move m(path.front(), path.back(), true);
        for (size_t i = 1; i < path.size() - 1; ++i)
            m.addToPath(path[i]);
        captures.emplace_back(m);
    }
}

std::vector<Move> Man::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    int dir = (color_ == Color::Black) ? 1 : -1;

    // Movimientos simples
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

    // Capturas simples y múltiples (exploración)
    std::vector<Move> captures;
    std::vector<Position> path = {from};
    exploreCaptures(board, from, color_, path, captures);
    moves.insert(moves.end(), captures.begin(), captures.end());
  
    return moves;
}
