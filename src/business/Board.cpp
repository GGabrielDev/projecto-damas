#include "Board.h"
#include "Piece.h"
#include "Man.h"
#include "King.h"

Board::Board()
    : squares_{} // value-initialize to nullptr
{
}

Board::~Board() {
    clear();
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

void Board::placePiece(const Position& pos, Piece* piece) {
    delete squares_[pos.row][pos.col];
    squares_[pos.row][pos.col] = piece;
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
