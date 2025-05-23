#ifndef RULEENGINE_H
#define RULEENGINE_H

#include <vector>
#include "Move.h"

class Board;
enum class Color;

class RuleEngine {
public:
    bool isValidMove(const Board& board, const Move& move) const;
    std::vector<Move> generateAllCaptures(const Board& board, Color playerColor) const;
    std::vector<Move> generateAllSimple(const Board& board, Color playerColor) const;
};

#endif // RULEENGINE_H
