#include "ConsoleUI.h"
#include <iomanip>

ConsoleUI::ConsoleUI(std::istream& input, std::ostream& output) 
    : input_(input), output_(output) {}

Move ConsoleUI::getPlayerMove(Color playerColor) const {
    output_ << (playerColor == Color::Black ? "Negras" : "Blancas") 
            << ", ingrese movimiento (ej: '2 3 -> 3 4'): ";
    
    std::string userInput;
    std::getline(input_, userInput); // Usa el stream de entrada inyectado
    
    std::istringstream iss(userInput);
    int fromRow, fromCol, toRow, toCol;
    std::string arrow;

    if (!(iss >> fromRow >> fromCol >> arrow >> toRow >> toCol) || arrow != "->") {
        throw std::invalid_argument("Formato inválido");
    }

    return Move(parsePosition(fromRow, fromCol), parsePosition(toRow, toCol));
}

void ConsoleUI::displayBoard(const Board& board) const {
    std::cout << "  ";
    for (int col = 0; col < 8; ++col) {
        std::cout << std::setw(2) << col;
    }
    std::cout << "\n";

    for (int row = 0; row < 8; ++row) {
        std::cout << row << " ";
        for (int col = 0; col < 8; ++col) {
            Position pos{row, col};
            if (!board.isEmpty(pos)) {
                Piece* p = board.getPiece(pos);
                char c = (p->color() == Color::Black) ? 'B' : 'W';
                if (p->type() == PieceType::King) c = toupper(c);
                std::cout << c << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

Position ConsoleUI::parsePosition(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        throw std::out_of_range("Posición fuera del tablero");
    }
    return {row, col};
}

void ConsoleUI::showMessage(const std::string& message) const {
    std::cout << "[INFO] " << message << "\n";
}

void ConsoleUI::showError(const std::string& error) const {
    std::cerr << "[ERROR] " << error << "\n";
}
