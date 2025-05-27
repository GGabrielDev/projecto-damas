#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "Position.h"

class Move {
public:
    Move() = default;
    Move(Position from, Position to, bool isCapture);

    Position from() const;
    Position to() const;
    bool isCapture() const;
    const std::vector<Position>& path() const;
    void addToPath(const Position& pos);
    void addIntermediate(const Position& pos);

private:
    Position from_;
    Position to_;
    bool isCapture_;
    std::vector<Position> path_;
};

#endif // MOVE_H
