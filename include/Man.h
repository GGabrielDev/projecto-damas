#ifndef MAN_H
#define MAN_H

#include "Piece.h"

class Man : public Piece {
public:
    Man(Color color);  // Constructor que especifica color y tipo PieceType::Man

    char type() const; // Devuelve el símbolo identificador (no se usa directamente en lógica de juego)

    // Sobrescribe el método virtual puro de Piece.
    // Genera todos los movimientos legales desde la posición dada.
    std::vector<Move> validMoves(const Board& board, const Position& from) const override;
};

#endif // MAN_H
