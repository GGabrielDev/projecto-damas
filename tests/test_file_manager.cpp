#include "FileManager.h"
#include "Man.h"
#include <cassert>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void test_save_and_list_and_load() {
    FileManager fm;

    // 1. Crear GameRecord con valores ficticios
    GameRecord rec;
    rec.gameType = "HumanVsHuman";
    rec.datetime = "20990101_000000";
    rec.result = "Empate";
    rec.moves = "2 3 3 4;5 4 4 3;";

    // 2. Crear un tablero con un estado simple
    Board board;
    board.clear();
    board.placePiece({2, 3}, new Man(Color::White));
    board.placePiece({5, 4}, new Man(Color::Black));

    // 3. Guardar el GameRecord con tablero
    bool ok = fm.saveGameRecord(rec, board);
    assert(ok && "saveGameRecord debería devolver true");

    // 4. Verificar existencia del archivo
    std::string expectedFilename = rec.gameType + "_" + rec.datetime + "_" + rec.result + ".txt";
    fs::path fullPath = fs::path("saves") / expectedFilename;
    assert(fs::exists(fullPath) && "El archivo guardado no existe en 'saves'");

    // 5. Verificar que listSavedGames incluya el archivo
    auto list = fm.listSavedGames();
    bool found = false;
    for (auto& name : list) {
        if (name == expectedFilename) {
            found = true;
            break;
        }
    }
    assert(found && "listSavedGames no incluyó el archivo recién guardado");

    // 6. Verificar que el contenido contenga movimientos y tablero
    std::string contenido = fm.loadGameRecord(expectedFilename);
    assert(!contenido.empty() && "loadGameRecord no devolvió contenido");

    assert(contenido.find("2 3 3 4;5 4 4 3;") != std::string::npos && "Movimientos no encontrados en archivo");
    assert(contenido.find("[Tablero Final]") != std::string::npos && "No se encontró etiqueta de tablero final");
    assert(contenido.find("2 | . . . b") != std::string::npos && "La pieza blanca no aparece en el tablero");
    assert(contenido.find("5 | . . . . n") != std::string::npos && "La pieza negra no aparece en el tablero");

    // 7. Cleanup
    fs::remove(fullPath);
    if (fs::is_empty("saves")) {
        fs::remove("saves");
    }

    std::cout << "[OK] test_save_and_list_and_load passed\n";
}

int main() {
    test_save_and_list_and_load();
    return 0;
}
