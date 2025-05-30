#include "ConsoleGame.h"
#include "Board.h"
#include "RuleEngine.h"
#include "GameResult.h"
#include "Man.h"
#include "King.h"
#include <iostream>
#include <sstream>
#include <limits>

namespace {
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void printMainMenu() {
        std::cout << "=============================================\n";
        std::cout << "    TODOPODEROSAS DAMAS - CONSOLE EDITION    \n";
        std::cout << "=============================================\n";
        std::cout << "1. Empezar Juego\n";
        std::cout << "2. Tutorial\n";
        std::cout << "3. Salir\n";
        std::cout << "Selecciona una opcion: ";
    }

    void printTutorial() {
        std::cout << "\n=== TUTORIAL ===\n";
        std::cout << "1. El juego es jugado en un tablero 8x8.\n";
        std::cout << "2. Cada jugador empieza con 12 piezas.\n";
        std::cout << "3. Solo hay movimientos diagonales en la dirección del oponente.\n";
        std::cout << "4. Realiza una captura al saltar a un cuadro sobre una ficha enemiga.\n";
        std::cout << "5. Alcanza el lado contrario para ascender a Rey y moverse de regreso.\n";
        std::cout << "6. Capturar el obligatorio si hay capturas disponibles.\n";
        std::cout << "7. El juego termina cuando el jugador no pueda moverse o no hayan mas piezas de un lado.\n\n";
    }

    void waitForEnter() {
        std::cout << "Presione ENTER para regresar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

ConsoleGame::ConsoleGame() : currentPlayer_(Color::White) {}

void ConsoleGame::start() {
    while (true) {
        printMainMenu();

        int option;
        std::cin >> option;

        clearScreen();

        if (option == 1) {
            playHumanVsHuman();
        } else if (option == 2) {
            printTutorial();
            waitForEnter();
        } else if (option == 3) {
            std::cout << "Adiós!\n";
            break;
        } else {
            std::cout << "Opción Invalida. Intente de nuevo.\n";
        }
    }
}

void ConsoleGame::playHumanVsHuman() {
    board_.initialize();
    currentPlayer_ = Color::White;

    while (true) {
        std::cout << "\n";
        printBoard();

        GameResult result;
        if (rules_.isGameOver(board_, currentPlayer_, result)) {
            // Use global to_string for GameResult
            std::cout << "\nSe acabo el juego! Resultado: " << ::to_string(result) << "\n";
            break;
        }

        std::cout << "Turno de las " << (currentPlayer_ == Color::White ? "Blancas" : "Negras") << "\n";
        std::cout << "Ingrese movimiento (ej. 2 3 3 4): fila origen, columna origen, fila destino, columna destino" << "\n> ";


        int fr, fc, tr, tc;
        std::cin >> fr >> fc >> tr >> tc;
        Position from{fr, fc}, to{tr, tc};

        clearScreen();

        // Convert GameResult to a human-readable C-string
        const char* to_string(GameResult result);
        Move move(from, to, false);

        // Detect capture automatically if possible
        auto captures = rules_.generateAllCaptures(board_, currentPlayer_);
        for (const auto& m : captures) {
            if (m.from() == from && m.to() == to)
                move = m;
        }

        if (rules_.isValidMove(board_, move)) {
            rules_.applyMove(board_, move);
            currentPlayer_ = (currentPlayer_ == Color::White ? Color::Black : Color::White);
        } else {
            std::cout << "Movimiento invalido. Intente de nuevo.\n";
        }
    }
}

void ConsoleGame::printBoard() const {
    std::cout << "     0 1 2 3 4 5 6 7\n";
    std::cout << "   -----------------\n";
    for (int row = 0; row < 8; ++row) {
        std::cout << " " << row << " |";
        for (int col = 0; col < 8; ++col) {
            const Piece* p = board_.getPiece({row, col});
            if (!p) {
                std::cout << " .";
            } else {
                char symbol = (p->type() == PieceType::Man) ? 'm' : 'k';
                symbol = (p->color() == Color::White) ? toupper(symbol) : symbol;
                std::cout << " " << symbol;
            }
        }
        std::cout << "\n";
    }
}
