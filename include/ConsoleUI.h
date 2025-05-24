#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "Board.h"
#include "Move.h"
#include "Position.h"
#include <iostream>
#include <sstream>

class ConsoleUI {
  public:
      ConsoleUI(std::istream& input = std::cin, std::ostream& output = std::cout);

      // Muestra el tablero en formato ASCII
      void displayBoard(const Board& board) const;

      // Solicita y parsea un movimiento (formato: "fila col -> fila col")
      Move getPlayerMove(Color playerColor) const;

      // Muestra mensajes al usuario
      void showMessage(const std::string& message) const;
      void showError(const std::string& error) const;

  private:
      std::istream& input_;
      std::ostream& output_;
      Position parsePosition(int row, int col) const;
};

#endif // CONSOLEUI_H
