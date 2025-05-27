#include "RuleEngine.h"
#include "Board.h"
#include "Man.h"
#include "King.h"
#include <algorithm>
#include <iostream>

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
    std::vector<Move> captures;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position pos{r, c};
            Piece* p = board.getPiece(pos);
            if (p && p->color() == playerColor) {
                auto moves = p->validMoves(board, pos);
                for (const auto& move : moves) {
                    if (move.isCapture())
                        captures.push_back(move);
                }
            }
        }
    }
    return captures;
}

void RuleEngine::applyMove(Board& board, const Move& move) const {
    const auto& path = move.path();
    if (move.isCapture()) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            Position from = path[i];
            Position to = path[i + 1];

            // Solo capturamos si es un salto de dos posiciones
            if (std::abs(from.row - to.row) == 2 && std::abs(from.col - to.col) == 2) {
                Position mid{(from.row + to.row) / 2, (from.col + to.col) / 2};

                if (mid.row < 0 || mid.row >= 8 || mid.col < 0 || mid.col >= 8) {
                    std::cerr << "[ERROR] Mid position out of bounds: (" << mid.row << "," << mid.col << ")\n";
                    continue;
                }

                Piece* target = board.getPiece(mid);
                if (!target) {
                    std::cerr << "[ERROR] Tried to capture empty square at: (" << mid.row << "," << mid.col << ")\n";
                } else {
                    board.removePiece(mid);
                }
            }

            board.movePiece(from, to);
        }
    } else {
        board.movePiece(move.from(), move.to());
    }
}
