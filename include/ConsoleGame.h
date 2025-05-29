#ifndef CONSOLE_GAME_H
#define CONSOLE_GAME_H

#include "Board.h"
#include "Piece.h"
#include "RuleEngine.h"

class ConsoleGame {
public:
    ConsoleGame();
    void run();

    void switchTurn();
    void printBoard() const;
private:
    Board board_;
    RuleEngine engine_;
    Color currentTurn_;
};

#endif // CONSOLE_GAME_H
