#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"

class AIPlayer : public Player {
public:
    AIPlayer(int depth);
    Move chooseMove(Board& board, RuleEngine& rules) override;

private:
    int depth_;
    int minimax(Board& board, int depth, bool maximizingPlayer, int alpha, int beta);
};

#endif // AIPLAYER_H
