#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Board.h"
#include "RuleEngine.h"
#include "Move.h"
#include "Position.h"

/// AIPlayer elige un movimiento legal usando RuleEngine.
/// Para profundidad > 1 podría implementarse minimax, pero aquí basta con 1.
class AIPlayer {
public:
    /// depth no se usa en esta versión básica, pero queda para futuro.
    explicit AIPlayer(int depth = 1);

    /// Devuelve un Move válido para el color activo (se asume que 
    /// el llamador sabe pasar el color correcto por RuleEngine).
    Move chooseMove(const Board& board, RuleEngine& engine);

private:
    int depth_;
};

#endif // AIPLAYER_H
