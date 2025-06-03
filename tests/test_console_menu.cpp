#include "ConsoleGame.h"
#include <iostream>
#include <sstream>
#include <cassert>

void test_main_menu_logic() {
    std::stringstream input("2\n\n3\n"); // Elige Tutorial, luego Enter, luego Salir
    std::stringstream output;

    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    ConsoleGame game;
    game.start();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string result = output.str();

    assert(result.find("TUTORIAL") != std::string::npos);
    assert(result.find("¡Adiós!") != std::string::npos);

    std::cout << "[OK] test_main_menu_logic passed\n";
}

int main() {
    test_main_menu_logic();
    return 0;
}
