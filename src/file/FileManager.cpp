#include "FileManager.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

bool FileManager::saveGameRecord(const GameRecord& record, const Board& board) const {
    fs::create_directories("saves");

    std::ostringstream filename;
    filename << "saves/" << record.gameType << "_"
             << record.datetime << "_" << record.result << ".txt";

    std::ofstream out(filename.str());
    if (!out.is_open()) return false;

    out << "[Tipo de Juego] " << record.gameType << "\n";
    out << "[Fecha y Hora]  " << record.datetime << "\n";
    out << "[Resultado]     " << record.result << "\n";
    out << "[Movimientos]   " << record.moves << "\n";
    out << "[Tablero Final]" << "\n";

    // Imprimir el tablero como en consola
    out << "     0 1 2 3 4 5 6 7\n";
    out << "   -----------------\n";
    for (int row = 0; row < 8; ++row) {
        out << " " << row << " |";
        for (int col = 0; col < 8; ++col) {
            const Piece* p = board.getPiece({row, col});
            if (!p) {
                out << " .";
            } else {
                char symbol;
                if (p->type() == PieceType::Man)
                    symbol = (p->color() == Color::White) ? 'b' : 'n';
                else
                    symbol = (p->color() == Color::White) ? 'B' : 'N';

                out << " " << symbol;
            }
        }
        out << "\n";
    }

    return true;
}

std::string FileManager::loadGameRecord(const std::string& filename) const {
    std::ifstream in("saves/" + filename);
    if (!in.is_open()) return "";

    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

std::vector<std::string> FileManager::listSavedGames() const {
    std::vector<std::string> result;
    if (!fs::exists("saves")) return result;

    for (const auto& entry : fs::directory_iterator("saves")) {
        if (entry.is_regular_file()) {
            result.push_back(entry.path().filename().string());
        }
    }
    return result;
}
