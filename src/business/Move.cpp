#include "Move.h"

Move::Move(Position from, Position to, bool capture)
    : from_(from), to_(to), isCapture_(capture) {
    path_.push_back(from);

    if (isCapture_) {
        int stepRow = (to.row - from.row) > 0 ? 1 : -1;
        int stepCol = (to.col - from.col) > 0 ? 1 : -1;
        for (int r = from.row + stepRow, c = from.col + stepCol; 
             r != to.row; 
             r += stepRow, c += stepCol) {
            path_.emplace_back(Position{r, c});
        }
    }

    path_.push_back(to);
}

Position Move::from() const {
    return from_;
}

Position Move::to() const {
    return to_;
}

bool Move::isCapture() const {
    return isCapture_;
}

const std::vector<Position>& Move::path() const {
    return path_;
}

void Move::addToPath(const Position& pos) {
    path_.insert(path_.end() - 1, pos);
}

void Move::addIntermediate(const Position& pos) {
    path_.insert(path_.end() - 1, pos);
}
