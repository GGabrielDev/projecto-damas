#include "Piece.h"

Piece::Piece(Color color, PieceType type) : color_(color), type_(type) {}
Piece::~Piece() {}
Color Piece::color() const { return color_; }
PieceType Piece::type() const { return type_; }
