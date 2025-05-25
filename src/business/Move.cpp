#include "Move.h"

Move::Move(Position from, Position to, bool capture)
    : from_(from), to_(to), isCapture_(capture) {
    path_.push_back(from);
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
