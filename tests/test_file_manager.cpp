#include "FileManager.h"
#include <cassert>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void test_save_and_list_and_load() {
    FileManager fm;
    // 1. Crear un GameRecord con valores constantes para facilitar la prueba
    GameRecord rec;
    rec.gameType = "HumanVsHuman";
    rec.datetime = "20990101_000000"; // fecha ficticia
    rec.result   = "Empate";
    rec.moves    = "2 3 3 4;5 4 4 3;";

    // 2. Llamar a saveGameRecord
    bool ok = fm.saveGameRecord(rec);
    assert(ok && "saveGameRecord debería devolver true");

    // 3. Construir el nombre esperado
    std::string expectedFilename = rec.gameType + "_" + rec.datetime + "_" + rec.result + ".txt";
    fs::path fullPath = fs::path("saves") / expectedFilename;
    assert(fs::exists(fullPath) && "El archivo guardado no existe en 'saves'");

    // 4. Verificar listSavedGames incluye ese nombre
    auto list = fm.listSavedGames();
    bool found = false;
    for (auto& name : list) {
        if (name == expectedFilename) {
            found = true;
            break;
        }
    }
    assert(found && "listSavedGames no incluyó el archivo recién guardado");

    // 5. Leer el contenido con loadGameRecord
    std::string contenido = fm.loadGameRecord(expectedFilename);
    assert(contenido == rec.moves && "loadGameRecord no devolvió el contenido esperado");

    // 6. Cleanup: eliminar el archivo de prueba
    // Limpieza del archivo
    fs::remove(fullPath);

    // Limpieza del directorio si está vacío
    if (fs::is_empty("saves")) {
        fs::remove("saves");
    }

    std::cout << "[OK] test_save_and_list_and_load passed\n";
}

int main() {
    test_save_and_list_and_load();
    return 0;
}
