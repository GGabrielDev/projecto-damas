#ifndef CONSOLE_GAME_H
#define CONSOLE_GAME_H

#include "Board.h"
#include "Piece.h"
#include "RuleEngine.h"
#include <vector>
#include <string>

/// Clase principal para gestionar el flujo de juego desde la consola.
class ConsoleGame {
public:
    ConsoleGame();  // Constructor por defecto

    void run();     // No implementado, pero queda como posible punto de entrada alternativo
    void start();   // Muestra menú principal y gestiona la navegación

    // Modos de juego
    void playHumanVsHuman();
    void playHumanVsAI();
    void playAIVsAI();

    // Dibuja el tablero en consola
    void printBoard() const;

    // Alterna el turno del jugador actual
    void switchTurn();

private:
    Board board_;                          // Estado del tablero
    RuleEngine rules_;                     // Motor de reglas del juego
    Color currentPlayer_;                  // Color del jugador actual
    std::vector<std::string> moveHistory_; // Historial de movimientos en formato "x y x' y'"
};

#endif // CONSOLE_GAME_H
