#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(Color color);
    std::vector<Move> validMoves(const Board& board, const Position& from) const override;
};

#endif // KING_H
