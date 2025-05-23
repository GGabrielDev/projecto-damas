#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Board.h"
#include "Player.h"
#include "RuleEngine.h"
#include "FileManager.h"

class Game {
public:
    Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2);
    void start();

private:
    Board board_;
    std::unique_ptr<Player> players_[2];
    RuleEngine rules_;
    FileManager fileManager_;
    int currentPlayerIndex_;

    void nextTurn();
    void end();
};

#endif // GAME_H
