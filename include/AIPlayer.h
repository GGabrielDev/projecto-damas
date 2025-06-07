#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Board.h"
#include "RuleEngine.h"
#include "Move.h"
#include "Position.h"

/// Representa un jugador controlado por IA.
/// En esta versión, la IA elige movimientos aleatoriamente entre los legales.
class AIPlayer {
public:
    /// depth es un valor reservado para futuras versiones con Minimax o similares.
    explicit AIPlayer(int depth = 1);

    /// Devuelve un movimiento válido para el color especificado usando el RuleEngine.
    Move chooseMove(const Board& board, RuleEngine& engine, Color color);

private:
    int depth_;  // No se usa aún, reservado para lógica de búsqueda profunda.
};

#endif // AIPLAYER_H
