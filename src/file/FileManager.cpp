#include "FileManager.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

static const char* SAVES_DIR = "saves";

bool FileManager::saveGameRecord(const GameRecord& record) const {
    // 1. Crear la carpeta "saves" si no existe
    std::error_code ec;
    if (!fs::exists(SAVES_DIR)) {
        if (!fs::create_directory(SAVES_DIR, ec)) {
            // No se pudo crear el directorio
            return false;
        }
    }

    // 2. Construir el nombre de archivo: "<gameType>_<datetime>_<result>.txt"
    std::ostringstream filename;
    filename << record.gameType << "_"
             << record.datetime << "_"
             << record.result << ".txt";

    fs::path fullPath = fs::path(SAVES_DIR) / filename.str();

    // 3. Abrir el archivo para escritura
    std::ofstream ofs(fullPath, std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        return false;
    }

    // 4. Escribir contenido: aquí simplemente usamos record.moves
    ofs << record.moves;
    ofs.close();
    return !ofs.fail();
}

std::vector<std::string> FileManager::listSavedGames() const {
    std::vector<std::string> result;
    std::error_code ec;

    // Si no existe la carpeta, devolvemos lista vacía
    if (!fs::exists(SAVES_DIR)) {
        return result;
    }

    // Iterar sobre cada entrada de "saves"
    for (const auto& entry : fs::directory_iterator(SAVES_DIR, ec)) {
        if (ec) break;
        if (!entry.is_regular_file()) continue;
        result.push_back(entry.path().filename().string());
    }
    return result;
}

std::string FileManager::loadGameRecord(const std::string& filename) const {
    fs::path fullPath = fs::path(SAVES_DIR) / filename;
    if (!fs::exists(fullPath) || !fs::is_regular_file(fullPath)) {
        return "";
    }

    std::ifstream ifs(fullPath, std::ios::in);
    if (!ifs.is_open()) {
        return "";
    }

    std::ostringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();
    return buffer.str();
}
