#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <vector>
#include "Move.h"

enum class GameOutcome { Win, Lose, Draw };

struct GameResult {
    GameOutcome outcome;
    std::vector<Move> moves;
};

#endif // GAMERESULT_H
