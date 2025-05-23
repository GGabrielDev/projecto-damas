#include "RuleEngine.h"
#include "Board.h"
#include "Man.h"
#include "King.h"
#include <vector>

namespace {
    bool isValidPosition(const Position& pos) {
        return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
    }
}

std::vector<Move> RuleEngine::generateAllSimple(const Board& board, Color playerColor) const {
    std::vector<Move> moves;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position pos{r, c};
            Piece* p = board.getPiece(pos);
            if (p && p->color() == playerColor) {
                auto vm = p->validMoves(board, pos);
                moves.insert(moves.end(), vm.begin(), vm.end());
            }
        }
    }
    return moves;
}

std::vector<Move> RuleEngine::generateAllCaptures(const Board& board, Color playerColor) const {
    std::vector<Move> captures;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position from{r, c};
            Piece* p = board.getPiece(from);
            if (p && p->color() == playerColor) {
                auto localCaptures = generatePieceCaptures(board, from, p);
                captures.insert(captures.end(), localCaptures.begin(), localCaptures.end());
            }
        }
    }
    return captures;
}

std::vector<Move> RuleEngine::generatePieceCaptures(const Board& board, const Position& from, const Piece* piece) const {
    std::vector<Move> captures;
    Color self = piece->color();

    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& [dr, dc] : directions) {
        Position over{from.row + dr, from.col + dc};
        Position landing{from.row + 2 * dr, from.col + 2 * dc};

        if (isValidPosition(over) && isValidPosition(landing)) {
            Piece* middle = board.getPiece(over);
            if (middle && middle->color() != self && board.isEmpty(landing)) {
                Move m(from, landing, true);
                captures.push_back(m);
            }
        }
    }

    return captures;
}

bool RuleEngine::isValidMove(const Board& board, const Move& move) const {
    Piece* p = board.getPiece(move.from());
    if (!p || board.getPiece(move.to()) != nullptr)
        return false;

    auto possibleMoves = p->validMoves(board, move.from());
    for (const auto& m : possibleMoves) {
        if (m.to() == move.to() && m.isCapture() == move.isCapture())
            return true;
    }
    return false;
}
