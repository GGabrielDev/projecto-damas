#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Board.h"
#include <string>
#include <vector>

/// Representa un registro de una partida jugada.
struct GameRecord {
    std::string gameType;   // Ej. "HumanVsHuman"
    std::string datetime;   // Formato: "YYYYMMDD_HHMMSS"
    std::string result;     // "BlancoGana", "NegroGana", "Empate"
    std::string moves;      // Cadena codificada: "2 3 3 4;5 4 4 3;..."
    std::string finalBoard; // Estado del tablero al finalizar
};

/// Clase encargada de guardar y recuperar partidas desde disco.
class FileManager {
public:
    /// Guarda un GameRecord como archivo .txt. Devuelve true si fue exitoso.
    bool saveGameRecord(const GameRecord& record, const Board& board) const;

    /// Devuelve una lista de nombres de archivos de partidas guardadas.
    std::vector<std::string> listSavedGames() const;

    /// Devuelve el contenido completo del archivo dado. Si no existe, retorna "".
    std::string loadGameRecord(const std::string& filename) const;
};

#endif // FILEMANAGER_H
