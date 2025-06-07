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

    // Devuelve el color de la pieza
    Color color() const;

    // Devuelve si es Peón (Man) o Rey (King)
    PieceType type() const;

    // Función virtual pura que cada subclase debe implementar
    // para calcular movimientos válidos según tipo y posición
    virtual std::vector<Move> validMoves(const Board& board, const Position& from) const = 0;

protected:
    Color color_;
    PieceType type_;
};

#endif // PIECE_H
