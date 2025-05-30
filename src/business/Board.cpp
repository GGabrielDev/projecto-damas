#include "Board.h"
#include "Man.h"
#include "King.h"
#include <cmath>
#include <iostream>

Board::Board()
    : squares_{} {}

Board::~Board() {
    clear();
}

Board::Board(const Board& other)
    : squares_{} {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (other.squares_[r][c]) {
                Piece* p = other.squares_[r][c];
                if (p->type() == PieceType::Man)
                    squares_[r][c] = new Man(p->color());
                else
                    squares_[r][c] = new King(p->color());
            } else {
                squares_[r][c] = nullptr;
            }
        }
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        clear();
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (other.squares_[r][c]) {
                    Piece* p = other.squares_[r][c];
                    if (p->type() == PieceType::Man)
                        squares_[r][c] = new Man(p->color());
                    else
                        squares_[r][c] = new King(p->color());
                } else {
                    squares_[r][c] = nullptr;
                }
            }
        }
    }
    return *this;
}

void Board::clear() {
    for (auto& row : squares_) {
        for (auto& cell : row) {
            if (cell) {
                delete cell;
                cell = nullptr;
            }
        }
    }
}

void Board::initialize() {
    clear();
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 8; ++col)
            if ((row + col) % 2 == 1)
                squares_[row][col] = new Man(Color::Black);

    for (int row = 5; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
            if ((row + col) % 2 == 1)
                squares_[row][col] = new Man(Color::White);
}

bool Board::isEmpty(const Position& pos) const {
    return squares_[pos.row][pos.col] == nullptr;
}

Piece* Board::getPiece(const Position& pos) const {
    return squares_[pos.row][pos.col];
}

void Board::movePiece(const Position& from, const Position& to) {
    Piece* p = squares_[from.row][from.col];
    squares_[to.row][to.col] = p;
    squares_[from.row][from.col] = nullptr;
    if (p->type() == PieceType::Man) {
        Color c = p->color();
        if ((c == Color::Black && to.row == 7) || (c == Color::White && to.row == 0)) {
            delete p;
            squares_[to.row][to.col] = new King(c);
        }

    }
}

void Board::removePiece(const Position& pos) {
    delete squares_[pos.row][pos.col];
    squares_[pos.row][pos.col] = nullptr;
}

void Board::placePiece(const Position& pos, Piece* piece) {
    delete squares_[pos.row][pos.col];
    squares_[pos.row][pos.col] = piece;
}

void Board::print() const {
    std::cout << "    0 1 2 3 4 5 6 7\n";
    std::cout << "   ----------------\n";
    for (int row = 0; row < 8; ++row) {
        std::cout << " " << row << " |";
        for (int col = 0; col < 8; ++col) {
            Piece* p = squares_[row][col];
            if (!p) {
                std::cout << " .";
            } else {
                char symbol = (p->type() == PieceType::Man) ? 'm' : 'k';
                symbol = (p->color() == Color::White) ? toupper(symbol) : symbol;
                std::cout << " " << symbol;
            }
        }
        std::cout << "\n";
    }
}
