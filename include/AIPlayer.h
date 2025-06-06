#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Board.h"
#include "RuleEngine.h"
#include "Move.h"
#include "Position.h"

/// AIPlayer elige un movimiento legal usando RuleEngine.
class AIPlayer {
public:
    /// depth no se usa en esta versión básica, pero queda para futuro.
    explicit AIPlayer(int depth = 1);

    /// Devuelve un Move válido para el color especificado
    Move chooseMove(const Board& board, RuleEngine& engine, Color color);

private:
    int depth_;
};

#endif // AIPLAYER_H
