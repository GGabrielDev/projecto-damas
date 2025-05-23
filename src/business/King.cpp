#include "King.h"

King::King(Color color) : Piece(color, PieceType::King) {}
std::vector<Move> King::validMoves(const Board& board, const Position& from) const {
    return {};  // Por implementar
}
