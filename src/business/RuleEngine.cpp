#include "RuleEngine.h"
#include "Board.h"
#include "Man.h"
#include "King.h"
#include <algorithm>
#include <unordered_map>

bool RuleEngine::isValidMove(const Board& board, const Move& move) const {
    auto captures = generateAllCaptures(board, board.getPiece(move.from())->color());
    if (!captures.empty()) {
        return std::any_of(captures.begin(), captures.end(), [&](const Move& m) {
            return m.from().row == move.from().row && m.from().col == move.from().col &&
                   m.to().row == move.to().row && m.to().col == move.to().col;
        });
    }
    auto simple = generateAllSimple(board, board.getPiece(move.from())->color());
    return std::any_of(simple.begin(), simple.end(), [&](const Move& m) {
        return m.from().row == move.from().row && m.from().col == move.from().col &&
               m.to().row == move.to().row && m.to().col == move.to().col;
    });
}

std::vector<Move> RuleEngine::generateAllSimple(const Board& board, Color playerColor) const {
    std::vector<Move> moves;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position pos{r, c};
            Piece* p = board.getPiece(pos);
            if (p && p->color() == playerColor) {
                auto vm = p->validMoves(board, pos);
                for (const auto& move : vm) {
                    if (!move.isCapture())
                        moves.push_back(move);
                }
            }
        }
    }
    return moves;
}

std::vector<Move> RuleEngine::generateAllCaptures(const Board& board, Color playerColor) const {
    std::unordered_map<int, Move> bestCapturesByFrom; // key: row*8 + col

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position pos{r, c};
            Piece* p = board.getPiece(pos);
            if (p && p->color() == playerColor) {
                auto moves = p->validMoves(board, pos);
                for (const auto& move : moves) {
                    if (!move.isCapture()) continue;
                    int key = move.from().row * 8 + move.from().col;
                    auto it = bestCapturesByFrom.find(key);
                    if (it == bestCapturesByFrom.end() || move.path().size() > it->second.path().size()) {
                        bestCapturesByFrom[key] = move;
                    }
                }
            }
        }
    }

    std::vector<Move> filtered;
    for (const auto& [_, m] : bestCapturesByFrom)
        filtered.push_back(m);
    return filtered;
}
