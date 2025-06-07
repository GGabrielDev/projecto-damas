#include "FileManager.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

/// Guarda un registro de partida en un archivo bajo "saves/".
/// Incluye encabezados, movimientos y el estado final del tablero.
bool FileManager::saveGameRecord(const GameRecord& record, const Board& board) const {
    fs::create_directories("saves");

    std::ostringstream filename;
    filename << "saves/" << record.gameType << "_"
             << record.datetime << "_" << record.result << ".txt";

    std::ofstream out(filename.str());
    if (!out.is_open()) return false;

    // Escribir metadatos
    out << "[Tipo de Juego] " << record.gameType << "\n";
    out << "[Fecha y Hora]  " << record.datetime << "\n";
    out << "[Resultado]     " << record.result << "\n";
    out << "[Movimientos]   " << record.moves << "\n";
    out << "[Tablero Final]" << "\n";

    // Dibujar el tablero tal como se ve en consola
    out << "     0 1 2 3 4 5 6 7\n";
    out << "   -----------------\n";
    for (int row = 0; row < 8; ++row) {
        out << " " << row << " |";
        for (int col = 0; col < 8; ++col) {
            const Piece* p = board.getPiece({row, col});
            if (!p) {
                out << " .";
            } else {
                // Determinar símbolo según tipo y color
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

/// Carga el contenido de un archivo guardado (como string completo).
std::string FileManager::loadGameRecord(const std::string& filename) const {
    std::ifstream in("saves/" + filename);
    if (!in.is_open()) return "";

    std::ostringstream ss;
    ss << in.rdbuf();  // Leer todo el archivo de una vez
    return ss.str();
}

/// Lista todos los archivos .txt dentro del directorio "saves/"
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
