#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

/// Representa un registro de partida (se guardará como texto en un archivo).
/// La parte “moves” puede ser, p. ej., una cadena con los movimientos separados por comas.
struct GameRecord {
    std::string gameType;   // "HumanVsHuman", "HumanVsAI", "AIvsAI"
    std::string datetime;   // Formato "YYYYMMDD_HHMMSS"
    std::string result;     // "BlancoGana", "NegroGana" o "Empate"
    std::string moves;      // Secuencia de movimientos, e.g. "2 3 3 4;5 4 4 3;..."
};

class FileManager {
public:
    /// Guarda un GameRecord completo. Crea (si no existía) el directorio "saves"
    /// y genera un archivo con nombre "<gameType>_<datetime>_<result>.txt".
    /// Devuelve true si todo se escribió correctamente, false en caso contrario.
    bool saveGameRecord(const GameRecord& record) const;

    /// Lista todos los archivos presentes en la carpeta "saves".
    /// Devuelve una lista de nombres de archivo (solo el nombre, no la ruta completa).
    std::vector<std::string> listSavedGames() const;

    /// Carga el contenido completo del archivo cuyo nombre es `filename`
    /// (debe existir en la carpeta "saves"). Devuelve su contenido como string.
    /// Si no existe o no se puede leer, retorna string vacío.
    std::string loadGameRecord(const std::string& filename) const;
};

#endif // FILEMANAGER_H
