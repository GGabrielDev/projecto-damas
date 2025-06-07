#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(Color color); // Constructor para una pieza tipo King

    // Similar a Man, pero permite moverse hacia cualquier dirección
    std::vector<Move> validMoves(const Board& board, const Position& from) const override;
};

#endif // KING_H
