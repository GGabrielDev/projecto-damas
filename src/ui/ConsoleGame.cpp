#include "ConsoleGame.h"
#include "Board.h"
#include "RuleEngine.h"
#include "GameResult.h"
#include "Man.h"
#include "King.h"
#include "FileManager.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <filesystem>

namespace {
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void printMainMenu() {
        std::cout << "=============================================" << '\n';
        std::cout << "    TODOPODEROSAS DAMAS - CONSOLE EDITION    " << '\n';
        std::cout << "=============================================" << '\n';
        std::cout << "1. Empezar Juego" << '\n';
        std::cout << "2. Tutorial" << '\n';
        std::cout << "3. Ver partidas guardadas" << '\n';
        std::cout << "4. Salir" << '\n';
        std::cout << "Selecciona una opcion: ";
    }

    void printTutorial() {
        std::cout << '\n' << "=== TUTORIAL ===" << '\n';
        std::cout << "1. El juego es jugado en un tablero 8x8." << '\n';
        std::cout << "2. Cada jugador empieza con 12 piezas." << '\n';
        std::cout << "3. Solo hay movimientos diagonales en la dirección del oponente." << '\n';
        std::cout << "4. Realiza una captura al saltar a un cuadro sobre una ficha enemiga." << '\n';
        std::cout << "5. Alcanza el lado contrario para ascender a Rey y moverte de regreso." << '\n';
        std::cout << "6. Capturar es obligatorio si hay capturas disponibles." << '\n';
        std::cout << "7. El juego termina cuando un jugador no puede moverse o no hay más piezas de un lado." << "\n\n";
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
        clearScreen();
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
            // Listar partidas guardadas
            FileManager fm;
            auto lista = fm.listSavedGames();
            if (lista.empty()) {
                std::cout << "No hay partidas guardadas." << '\n';
            } else {
                std::cout << "Partidas guardadas:" << '\n';
                int idx = 1;
                for (const auto& nombre : lista) {
                    std::cout << " " << idx++ << ". " << nombre << '\n';
                }
                std::cout << "Selecciona número para ver detalles (0 para volver): ";
                int sel; std::cin >> sel;
                clearScreen();
                if (sel > 0 && sel <= (int)lista.size()) {
                    auto contenido = fm.loadGameRecord(lista[sel - 1]);
                    std::cout << "--- Contenido de " << lista[sel - 1] << " ---" << '\n';
                    std::cout << contenido << '\n';
                    std::cout << "-------------------------------" << "\n";
                    waitForEnter();
                }
            }
        } else if (option == 4) {
            std::cout << "¡Adiós!" << '\n';
            break;
        } else {
            std::cout << "Opción inválida. Intente de nuevo." << '\n';
            waitForEnter();
        }
    }
}

void ConsoleGame::playHumanVsHuman() {
    board_.initialize();
    moveHistory_.clear();
    currentPlayer_ = Color::White;

    while (true) {
        clearScreen();
        std::cout << '\n';
        printBoard();

        GameResult resultado;
        if (rules_.isGameOver(board_, currentPlayer_, resultado)) {
            std::cout << "\nSe acabó el juego! Resultado: " << ::to_string(resultado) << "\n";
            
            // Construir timestamp
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            std::tm tm{};
        #ifdef _WIN32
            localtime_s(&tm, &t);
        #else
            localtime_r(&t, &tm);
        #endif
            std::ostringstream ss;
            ss << std::put_time(&tm, "%Y%m%d_%H%M%S");
            std::string timestamp = ss.str();

            // Convertir resultado a texto
            std::string resultadoStr;
            switch (resultado) {
                case GameResult::WinWhite: resultadoStr = "BlancoGana"; break;
                case GameResult::WinBlack: resultadoStr = "NegroGana";  break;
                case GameResult::Draw:     resultadoStr = "Empate";      break;
                default:                   resultadoStr = "EnJuego";     break;
            }

            // Concatenar movimientos
            std::ostringstream movesOss;
            for (size_t i = 0; i < moveHistory_.size(); ++i) {
                movesOss << moveHistory_[i];
                if (i + 1 < moveHistory_.size()) movesOss << ";";
            }
            std::string movesStr = movesOss.str();

            // Crear y guardar GameRecord
            GameRecord rec;
            rec.gameType = "HumanVsHuman";
            rec.datetime = timestamp;
            rec.result   = resultadoStr;
            rec.moves    = movesStr;

            FileManager fm;
            if (fm.saveGameRecord(rec)) {
                std::cout << "Partida guardada en \"saves/"
                          << rec.gameType << "_" << rec.datetime 
                          << "_" << rec.result << ".txt\"" << "\n";
            } else {
                std::cout << "Error al guardar la partida." << "\n";
            }

            waitForEnter();
            break;
        }

        std::cout << "Turno de las " << (currentPlayer_ == Color::White ? "Blancas" : "Negras") << "\n";
        std::cout << "Ingrese movimiento (ej. 2 3 3 4): fila origen, columna origen, fila destino, columna destino" << "\n> ";

        int fr, fc, tr, tc;
        std::cin >> fr >> fc >> tr >> tc;
        Position from{fr, fc}, to{tr, tc};
        clearScreen();

        Move move(from, to, false);
        auto captures = rules_.generateAllCaptures(board_, currentPlayer_);
        for (const auto& m : captures) {
            if (m.from() == from && m.to() == to) {
                move = m;
                break;
            }
        }

        if (rules_.isValidMove(board_, move)) {
            rules_.applyMove(board_, move);
            // Registrar movimiento
            std::ostringstream oss;
            oss << from.row << " " << from.col << " " << to.row << " " << to.col;
            moveHistory_.push_back(oss.str());

            currentPlayer_ = (currentPlayer_ == Color::White ? Color::Black : Color::White);
        } else {
            std::cout << "Movimiento inválido. Intente de nuevo." << "\n";
            waitForEnter();
        }
    }
}

void ConsoleGame::printBoard() const {
    std::cout << "     0 1 2 3 4 5 6 7" << "\n";
    std::cout << "   -----------------" << "\n";
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
