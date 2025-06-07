#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "Position.h"

/// Representa un movimiento desde una posición hasta otra.
/// Puede incluir múltiples posiciones si es una cadena de capturas.
class Move {
public:
    Move(Position from, Position to, bool isCapture);

    Position from() const;
    Position to() const;
    bool isCapture() const;

    const std::vector<Position>& path() const;

    /// Inserta una posición intermedia en la trayectoria del movimiento (útil para múltiples capturas)
    void addToPath(const Position& pos);

    /// Igual que addToPath, pero con nombre más descriptivo (alias)
    void addIntermediate(const Position& pos);

private:
    Position from_;                  // Posición de origen
    Position to_;                    // Posición final
    bool isCapture_;                 // Indica si es un movimiento de captura
    std::vector<Position> path_;     // Secuencia de posiciones desde 'from' hasta 'to', incluyendo intermedios
};

#endif // MOVE_H
