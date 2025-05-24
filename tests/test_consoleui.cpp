#include <cassert>
#include <sstream>
#include <iostream>
#include "ConsoleUI.h"
#include "Board.h"

void testDisplayBoard() {
    Board board;
    board.initialize();
    ConsoleUI ui;

    // Redirigir cout a un buffer
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    ui.displayBoard(board);

    // Restaurar cout
    std::cout.rdbuf(old);

    // Verificar encabezado de columnas
    std::string output = buffer.str();
    assert(output.find("0 1 2 3 4 5 6 7") != std::string::npos);
    assert(output.find("B . B . B . B .") != std::string::npos); // Fila inicial negra
    std::cout << "[OK] Display board test passed.\n";
}

void testParseValidMove() {
    std::istringstream input("2 3 -> 3 4");
    std::ostringstream output;
    ConsoleUI ui(input, output);

    Move m = ui.getPlayerMove(Color::Black);
    
    assert(m.from().row == 2);
    assert(m.from().col == 3);
    assert(m.to().row == 3);
    assert(m.to().col == 4);
    std::cout << "[OK] Valid move parsing test passed.\n";
}

int main() {
    testParseValidMove();
    return 0;
}
