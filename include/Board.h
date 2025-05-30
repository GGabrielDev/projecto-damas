#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Piece.h"
#include "Move.h"
#include "Position.h"

class Board {
public:
    Board();
    Board(const Board& other); // copia profunda
    Board& operator=(const Board& other); // asignacion profunda
    ~Board();

    void clear();
    void initialize();
    void placePiece(const Position& pos, Piece* piece);
    bool isEmpty(const Position& pos) const;
    Piece* getPiece(const Position& pos) const;
    void movePiece(const Position& from, const Position& to);
    void removePiece(const Position& pos);
    void print() const;

private:
    std::array<std::array<Piece*, 8>, 8> squares_;
};

#endif // BOARD_H
