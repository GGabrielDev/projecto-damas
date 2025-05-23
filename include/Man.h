#ifndef MAN_H
#define MAN_H

#include "Piece.h"

class Man : public Piece {
public:
    Man(Color color);
    std::vector<Move> validMoves(const Board& board, const Position& from) const override;
};

#endif // MAN_H
