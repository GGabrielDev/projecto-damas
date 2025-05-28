#include "RuleEngine.h"
#include "Board.h"
#include "GameResult.h"
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

bool RuleEngine::isGameOver(const Board& board, Color currentPlayer, GameResult& result) const {
    bool hasPieces = false;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board.getPiece({r, c});
            if (p && p->color() == currentPlayer) {
                hasPieces = true;
                break;
            }
        }
    }

    if (!hasPieces) {
        result = (currentPlayer == Color::White) ? GameResult::WinBlack : GameResult::WinWhite;
        std::cout << "[DEBUG] No hay piezas restantes\n";
        return true;
    }

    auto captures = generateAllCaptures(board, currentPlayer);
    if (!captures.empty()) {
        std::cout << "[DEBUG] Hay capturas válidas:\n";
        for (const auto& m : captures) {
            std::cout << "  Captura: ";
            for (const auto& p : m.path()) {
                std::cout << "(" << p.row << "," << p.col << ") ";
            }
            std::cout << std::endl;
        }
        result = GameResult::Ongoing;
        return false;
    }

    auto simple = generateAllSimple(board, currentPlayer);
    if (!simple.empty()) {
        std::cout << "[DEBUG] Hay movimientos simples válidos:\n";
        for (const auto& m : simple) {
            std::cout << "  De (" << m.from().row << "," << m.from().col << ") a ("
                      << m.to().row << "," << m.to().col << ")\n";
        }
        result = GameResult::Ongoing;
        return false;
    }

    result = (currentPlayer == Color::White) ? GameResult::WinBlack : GameResult::WinWhite;
    std::cout << "[DEBUG] No hay movimientos válidos restantes\n";
    return true;
}
