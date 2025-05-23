#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "Position.h"

class Move {
public:
    Move(const Position& from, const Position& to, bool capture=false);
    const Position& from() const;
    const Position& to() const;
    bool isCapture() const;
    const std::vector<Position>& path() const;

private:
    Position from_;
    Position to_;
    bool isCapture_;
    std::vector<Position> path_;
};

#endif // MOVE_H
