#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"

class Board;
class RuleEngine;

class Player {
public:
    virtual ~Player();
    virtual Move chooseMove(Board& board, RuleEngine& rules) = 0;
};

#endif // PLAYER_H
