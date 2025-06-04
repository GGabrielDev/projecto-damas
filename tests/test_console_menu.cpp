#include "ConsoleGame.h"
#include <iostream>
#include <sstream>
#include <cassert>

void test_main_menu_logic() {
    // 1) “2” para Tutorial 
    // 2) ENTER para regresar del tutorial 
    // 3) “4” para Salir
    std::stringstream input("2\n\n4\n"); 
    std::stringstream output;

    // Redireccionar stdin/stdout
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    ConsoleGame game;
    game.start();

    // Restaurar stdin/stdout
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string result = output.str();

    // Validar que se mostró el tutorial y luego “¡Adiós!”
    assert(result.find("TUTORIAL") != std::string::npos);
    assert(result.find("¡Adiós!") != std::string::npos);

    std::cout << "[OK] test_main_menu_logic passed\n";
}

int main() {
    test_main_menu_logic();
    return 0;
}
