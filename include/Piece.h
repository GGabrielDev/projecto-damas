#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Move.h"
#include "Position.h"

// Declaración Forward para evitar dependencia circular
class Board;

enum class Color { Black, White };
enum class PieceType { Man, King };

class Piece {
public:
    Piece(Color color, PieceType type);
    virtual ~Piece();
    Color color() const;
    PieceType type() const;
    virtual std::vector<Move> validMoves(const Board& board, const Position& from) const = 0;

protected:
    Color color_;
    PieceType type_;
};

#endif // PIECE_H
