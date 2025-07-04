#include "AIPlayer.h"
#include "Board.h"
#include "ConsoleGame.h"
#include "FileManager.h"
#include "GameResult.h"
#include "King.h"
#include "Man.h"
#include "RuleEngine.h"
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
        std::cout << "1. Humano vs Humano" << '\n';
        std::cout << "2. Humano vs IA" << '\n';
        std::cout << "3. IA vs IA" << '\n';
        std::cout << "4. Tutorial" << '\n';
        std::cout << "5. Ver partidas guardadas" << '\n';
        std::cout << "6. Salir" << '\n';
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

    bool readInt(int& out) {
        if (!(std::cin >> out)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    std::string buildFilename(const std::string& tipo, const std::string& resultado) {
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
        return tipo + "_" + ss.str() + "_" + resultado;
    }

    /// O(H) / H = historial de movimientos (longitud T)
    void saveGame(const std::string& tipo, const std::string& resultado, const std::vector<std::string>& history, const Board& board) {
        std::ostringstream movesOss;
        for (size_t i = 0; i < history.size(); ++i) {
            movesOss << history[i];
            if (i + 1 < history.size()) movesOss << ";";
        }

        GameRecord rec;
        rec.gameType = tipo;
        rec.datetime = buildFilename(tipo, resultado);
        rec.result = resultado;
        rec.moves = movesOss.str();

        // Agrega el estado final del tablero
        std::ostringstream boardStr;
        boardStr << "     0 1 2 3 4 5 6 7\n";
        boardStr << "   -----------------\n";
        for (int row = 0; row < 8; ++row) {
            boardStr << " " << row << " |";
            for (int col = 0; col < 8; ++col) {
                const Piece* p = board.getPiece({row, col});
                if (!p) {
                    boardStr << " .";
                } else {
                    char symbol;
                    if (p->color() == Color::White)
                        symbol = (p->type() == PieceType::Man) ? 'b' : 'B';
                    else
                        symbol = (p->type() == PieceType::Man) ? 'n' : 'N';
                    boardStr << " " << symbol;
                }
            }
            boardStr << "\n";
        }
        rec.finalBoard = boardStr.str();

        FileManager fm;
        if (fm.saveGameRecord(rec, board)) {
            std::cout << "Partida guardada en \"saves/" << rec.datetime << ".txt\"\n";
        } else {
            std::cout << "Error al guardar la partida.\n";
        }
    }
}  

ConsoleGame::ConsoleGame() : currentPlayer_(Color::White) {}

/// O(M) / M = iteraciones hasta salir (depende del usuario)
void ConsoleGame::start() {
    while (true) {
        clearScreen();
        printMainMenu();

        int option;
        if (!readInt(option)) {
            std::cout << "Entrada inválida. Intente con un número del 1 al 6." << '\n';
            waitForEnter();
            continue;
        }
        clearScreen();

        switch (option) {
            case 1:
                playHumanVsHuman();
                break;
            case 2:
                playHumanVsAI();
                break;
            case 3:
                playAIVsAI();
                break;
            case 4:
                printTutorial();
                waitForEnter();
                break;
            case 5: {
                FileManager fm;
                auto lista = fm.listSavedGames();
                if (lista.empty()) {
                    std::cout << "No hay partidas guardadas." << '\n';
                    waitForEnter();
                } else {
                    std::cout << "Partidas guardadas:" << '\n';
                    int idx = 1;
                    for (const auto& nombre : lista) {
                        std::cout << " " << idx++ << ". " << nombre << '\n';
                    }
                    std::cout << "Selecciona número para ver detalles (0 para volver): ";
                    int sel;
                    if (!readInt(sel)) {
                        std::cout << "Entrada inválida. Volviendo al menú." << '\n';
                        waitForEnter();
                        break;
                    }
                    clearScreen();
                    if (sel > 0 && sel <= static_cast<int>(lista.size())) {
                        auto contenido = fm.loadGameRecord(lista[sel - 1]);
                        std::cout << "--- Contenido de " << lista[sel - 1] << " ---" << '\n';
                        std::cout << contenido << '\n';
                        std::cout << "-------------------------------" << "\n";
                        waitForEnter();
                    }
                }
                break;
            }
            case 6:
                std::cout << "¡Adiós!" << '\n';
                return;
            default:
                std::cout << "Opción inválida. Intente de nuevo." << '\n';
                waitForEnter();
                break;
        }
    }
}

/// O(T × (1 + H)) / T = turnos, H = intentos humanos por turno
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

            std::string resultadoStr;
            switch (resultado) {
                case GameResult::WinWhite: resultadoStr = "BlancoGana"; break;
                case GameResult::WinBlack: resultadoStr = "NegroGana";  break;
                case GameResult::Draw:     resultadoStr = "Empate";      break;
                default:                   resultadoStr = "EnJuego";     break;
            }

            std::ostringstream movesOss;
            for (size_t i = 0; i < moveHistory_.size(); ++i) {
                movesOss << moveHistory_[i];
                if (i + 1 < moveHistory_.size()) movesOss << ";";
            }
            std::string movesStr = movesOss.str();

            GameRecord rec;
            rec.gameType = "HumanVsHuman";
            rec.datetime = timestamp;
            rec.result   = resultadoStr;
            rec.moves    = movesStr;

            FileManager fm;
            if (fm.saveGameRecord(rec, board_)) {
                std::cout << "Partida guardada en \"saves/"
                          << rec.gameType << "_" << rec.datetime 
                          << "_" << rec.result << ".txt\"" << "\n";
            } else {
                std::cout << "Error al guardar la partida." << "\n";
            }

            waitForEnter();
            return;
        }

        std::cout << "Turno de las " << (currentPlayer_ == Color::White ? "Blancas" : "Negras") << "\n";
        std::cout << "Ingrese movimiento (ej. 2 3 3 4): fila origen, columna origen, fila destino, columna destino" << "\n> ";

        int fr, fc, tr, tc;
        if (!readInt(fr) || !readInt(fc) || !readInt(tr) || !readInt(tc)) {
            std::cout << "Entrada inválida. Use cuatro números separados por espacios." << "\n";
            waitForEnter();
            continue;
        }
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

/// O(1) / 8x8 = 64 operaciones (constante)
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
                char symbol;
                if (p->color() == Color::White) {
                    symbol = (p->type() == PieceType::Man) ? 'b' : 'B';
                } else {
                    symbol = (p->type() == PieceType::Man) ? 'n' : 'N';
                }
                std::cout << " " << symbol;
            }
        }
        std::cout << "\n";
    }
}

/// O(T × (1 + H + A)) / A = complejidad de la IA
void ConsoleGame::playHumanVsAI() {
    board_.initialize();
    moveHistory_.clear();
    currentPlayer_ = Color::White;
    AIPlayer ai(/*depth=*/1);

    while (true) {
        clearScreen();
        std::cout << "\n";
        printBoard();

        GameResult result;
        if (rules_.isGameOver(board_, currentPlayer_, result)) {
            std::cout << "\nSe acabó el juego! Resultado: " << ::to_string(result) << "\n";
            saveGame("HumanVsAI", to_string(result), moveHistory_, board_);
            waitForEnter();
            return;
        }

        if (currentPlayer_ == Color::White) {
            std::cout << "Turno del Humano (Blancas)\n";
            std::cout << "Ingrese movimiento (ej. 2 3 3 4): ";

            int fr, fc, tr, tc;
            if (!readInt(fr) || !readInt(fc) || !readInt(tr) || !readInt(tc)) {
                std::cout << "Entrada inválida. Use cuatro números separados por espacios.\n";
                waitForEnter();
                continue;
            }

            Position from{fr, fc}, to{tr, tc};
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
                std::ostringstream oss;
                oss << from.row << " " << from.col << " " << to.row << " " << to.col;
                moveHistory_.push_back(oss.str());
                currentPlayer_ = Color::Black;
            } else {
                std::cout << "Movimiento inválido. Intente de nuevo.\n";
                waitForEnter();
            }
        } else {
            std::cout << "Turno de la IA (Negras)...\n";
            Move aiMove = ai.chooseMove(board_, rules_, Color::Black);
            if (aiMove.from().row != -1) {
                rules_.applyMove(board_, aiMove);
                std::ostringstream oss;
                oss << aiMove.from().row << " " << aiMove.from().col << " "
                    << aiMove.to().row << " " << aiMove.to().col;
                moveHistory_.push_back(oss.str());
            }
            currentPlayer_ = Color::White;
        }
    }
}

/// O(T × (A1 + A2)) / A1/A2 = complejidad de cada IA
void ConsoleGame::playAIVsAI() {
    board_.initialize();
    moveHistory_.clear();
    currentPlayer_ = Color::White;
    AIPlayer whiteAI(1);
    AIPlayer blackAI(1);
    int nonProgressTurns = 0;

    while (true) {
        clearScreen();
        std::cout << "\n";
        printBoard();

        GameResult result;
        if (rules_.isGameOver(board_, currentPlayer_, result)) {
            std::cout << "\nSe acabó el juego! Resultado: " << ::to_string(result) << "\n";
            saveGame("AIvsAI", to_string(result), moveHistory_, board_);
            waitForEnter();
            return;
        }

        int whiteCount = board_.countPieces(Color::White);
        int blackCount = board_.countPieces(Color::Black);
        if (whiteCount <= 6 && blackCount <= 6 && nonProgressTurns >= 40) {
            std::cout << "\nSe declara empate por inactividad prolongada.\n";
            saveGame("AIvsAI", "Empate", moveHistory_, board_);
            waitForEnter();
            return;
        }

        std::cout << "Turno de la IA (" << (currentPlayer_ == Color::White ? "Blancas" : "Negras") << ")...\n";
        AIPlayer& currentAI = (currentPlayer_ == Color::White) ? whiteAI : blackAI;
        Move move = currentAI.chooseMove(board_, rules_, currentPlayer_);

        if (move.from().row != -1) {
            bool wasCapture = move.isCapture();
            bool wasPromotion = false;
            Piece* before = board_.getPiece(move.from());

            rules_.applyMove(board_, move);

            Piece* after = board_.getPiece(move.to());
            if (before && after && before != after && after->type() == PieceType::King)
                wasPromotion = true;

            if (wasCapture || wasPromotion)
                nonProgressTurns = 0;
            else
                ++nonProgressTurns;

            std::ostringstream oss;
            oss << move.from().row << " " << move.from().col << " "
                << move.to().row << " " << move.to().col;
            moveHistory_.push_back(oss.str());
        }

        currentPlayer_ = (currentPlayer_ == Color::White) ? Color::Black : Color::White;
    }
}
