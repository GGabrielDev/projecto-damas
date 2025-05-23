#include "RuleEngine.h"
#include "Board.h"

bool RuleEngine::isValidMove(const Board& board, const Move& move) const {
    // Por ahora considera solo movimientos simples
    auto allSimple = generateAllSimple(board, move.from().row < move.to().row ? Color::Black : Color::White);
    for (auto& m : allSimple) {
        if (m.from().row == move.from().row && m.from().col == move.from().col &&
            m.to().row == move.to().row && m.to().col == move.to().col)
            return true;
    }
    return false;
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

std::vector<Move> RuleEngine::generateAllCaptures(const Board& board, Color /*playerColor*/) const {
    // Implementación futura
    return {};
}

