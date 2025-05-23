#include "Move.h"

Move::Move(const Position& from, const Position& to, bool capture)
    : from_(from), to_(to), isCapture_(capture) {
    path_.push_back(from);
    path_.push_back(to);
}

const Position& Move::from() const { return from_; }
const Position& Move::to() const { return to_; }
bool Move::isCapture() const { return isCapture_; }
const std::vector<Position>& Move::path() const { return path_; }
