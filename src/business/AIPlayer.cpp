#include "AIPlayer.h"
#include <random>
#include <algorithm>

AIPlayer::AIPlayer(int depth)
    : depth_(depth)
{}

/// Elige un movimiento válido para el color proporcionado.
/// - Si hay capturas disponibles, elige una aleatoriamente (obligatorias).
/// - Si no, elige un movimiento simple aleatoriamente.
/// - Si no hay ningún movimiento válido, retorna un movimiento "nulo".
Move AIPlayer::chooseMove(const Board& board, RuleEngine& engine, Color color) {
    auto captures = engine.generateAllCaptures(board, color);
    if (!captures.empty()) {
        // Aleatoriza el orden de las capturas para que no repita siempre
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(captures.begin(), captures.end(), g);
        return captures.front(); // Toma la primera tras mezclar
    }

    auto simple = engine.generateAllSimple(board, color);
    if (!simple.empty()) {
        // Aleatoriza los movimientos simples
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(simple.begin(), simple.end(), g);
        return simple.front();
    }

    // Si no hay movimientos válidos, devuelve un movimiento inválido
    return Move({-1, -1}, {-1, -1}, false);
}
