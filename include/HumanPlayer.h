#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

/// Representa un jugador humano que elige manualmente los movimientos.
class HumanPlayer : public Player {
public:
    /// Elige un movimiento mediante entrada del usuario (definición en otro lado)
    Move chooseMove(Board& board, RuleEngine& rules) override;
};

#endif // HUMANPLAYER_H
