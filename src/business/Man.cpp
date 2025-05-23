#include "Man.h"

Man::Man(Color color) : Piece(color, PieceType::Man) {}
std::vector<Move> Man::validMoves(const Board& board, const Position& from) const {
    return {};  // Por implementar
}
