#include "AIPlayer.h"

AIPlayer::AIPlayer(int depth)
    : depth_(depth)
{}

Move AIPlayer::chooseMove(const Board& board, RuleEngine& engine, Color color) {
    auto captures = engine.generateAllCaptures(board, color);
    if (!captures.empty()) {
        return captures.front();
    }

    auto simple = engine.generateAllSimple(board, color);
    if (!simple.empty()) {
        return simple.front();
    }

    // Movimiento nulo si no hay disponibles
    return Move({-1, -1}, {-1, -1}, false);
}
