#ifndef RULEENGINE_H
#define RULEENGINE_H

#include <vector>
#include "Board.h"
#include "Move.h"
#include "Position.h"
#include "Piece.h"

class Board;
enum class Color;

class RuleEngine {
public:
    bool isValidMove(const Board& board, const Move& move) const;
    std::vector<Move> generateAllSimple(const Board& board, Color playerColor) const;
    std::vector<Move> generateAllCaptures(const Board& board, Color playerColor) const;

private:
    std::vector<Move> generatePieceCaptures(const Board& board, const Position& from, const Piece* piece) const;
};

#endif // RULEENGINE_H
