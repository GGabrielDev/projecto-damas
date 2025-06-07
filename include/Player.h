#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"

class Board;
class RuleEngine;

/// Clase base abstracta para representar un jugador (humano o IA).
class Player {
public:
    virtual ~Player() = default;

    /// Cada jugador debe implementar esta función para decidir su movimiento.
    virtual Move chooseMove(Board& board, RuleEngine& rules) = 0;
};

#endif // PLAYER_H
