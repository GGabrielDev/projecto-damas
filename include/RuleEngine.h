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

class RuleEngine {
public:
    void applyMove(Board& board, const Move& move) const;
    bool isValidMove(const Board& board, const Move& move) const;
    bool isGameOver(const Board& board, Color currentPlayer, GameResult& result) const;
    std::vector<Move> generateAllSimple(const Board& board, Color playerColor) const;
    std::vector<Move> generateAllCaptures(const Board& board, Color playerColor) const;

private:
    std::vector<Move> generatePieceCaptures(const Board& board, const Position& from, const Piece* piece) const;
};

#endif // RULEENGINE_H
