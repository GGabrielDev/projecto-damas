#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Piece.h"
#include "Move.h"

class Board {
public:
    Board();
    void initialize();
    bool isEmpty(const Position& pos) const;
    Piece* getPiece(const Position& pos) const;
    void movePiece(const Position& from, const Position& to);
    void removePiece(const Position& pos);

private:
    std::array<std::array<Piece*, 8>, 8> squares_;
};

#endif // BOARD_H
