#include "AIPlayer.h"
#include <random>
#include <algorithm>

AIPlayer::AIPlayer(int depth)
    : depth_(depth)
{}

Move AIPlayer::chooseMove(const Board& board, RuleEngine& engine, Color color) {
    auto captures = engine.generateAllCaptures(board, color);
    if (!captures.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(captures.begin(), captures.end(), g);
        return captures.front();
    }

    auto simple = engine.generateAllSimple(board, color);
    if (!simple.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(simple.begin(), simple.end(), g);
        return simple.front();
    }

    // Movimiento nulo si no hay disponibles
    return Move({-1, -1}, {-1, -1}, false);
}
