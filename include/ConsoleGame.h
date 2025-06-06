#ifndef CONSOLE_GAME_H
#define CONSOLE_GAME_H

#include "Board.h"
#include "Piece.h"
#include "RuleEngine.h"
#include <vector>
#include <string>

class ConsoleGame {
public:
    ConsoleGame();
    void run();
    void start();
    void playHumanVsHuman();
    void playHumanVsAI();
    void playAIVsAI();
    void printBoard() const;
    void switchTurn();

private:
    Board board_;
    RuleEngine rules_;
    Color currentPlayer_;
    std::vector<std::string> moveHistory_;
};

#endif // CONSOLE_GAME_H
