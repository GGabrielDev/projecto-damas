#ifndef CONSOLE_GAME_H
#define CONSOLE_GAME_H

#include "Board.h"
#include "Piece.h"
#include "RuleEngine.h"

class ConsoleGame {
public:
    ConsoleGame();
    void run();                      // aún presente, puede ser usado para simulaciones
    void start();                    // punto de entrada interactivo principal
    void playHumanVsHuman();        // modo principal de juego
    void printBoard() const;        // accesible desde pruebas

    void switchTurn();

private:
    Board board_;
    RuleEngine rules_;
    Color currentPlayer_;
};

#endif // CONSOLE_GAME_H
