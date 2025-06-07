#ifndef RULEENGINE_H
#define RULEENGINE_H

#include "Board.h"
#include "GameResult.h"
#include "Move.h"
#include "Position.h"
#include "Piece.h"
#include <vector>

class Board;
enum class Color;

/// Regla general del motor del juego.
/// Esta clase centraliza toda la lógica para validar, aplicar movimientos,
/// y verificar si una partida ha terminado.
class RuleEngine {
public:
    /// Aplica un movimiento en el tablero, ya sea simple o de captura.
    void applyMove(Board& board, const Move& move) const;

    /// Verifica si un movimiento dado es legal para el jugador actual.
    bool isValidMove(const Board& board, const Move& move) const;

    /// Determina si el juego terminó para un jugador y devuelve el resultado.
    bool isGameOver(const Board& board, Color currentPlayer, GameResult& result) const;

    /// Genera todos los movimientos simples posibles para el jugador dado.
    std::vector<Move> generateAllSimple(const Board& board, Color playerColor) const;

    /// Genera todos los movimientos de captura posibles para el jugador dado.
    std::vector<Move> generateAllCaptures(const Board& board, Color playerColor) const;

private:
    /// Ayudante para generar las capturas válidas desde una pieza específica.
    std::vector<Move> generatePieceCaptures(const Board& board, const Position& from, const Piece* piece) const;
};

#endif // RULEENGINE_H
