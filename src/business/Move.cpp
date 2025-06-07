#include "Move.h"

/// Constructor de movimiento
/// Si es una captura, se genera una trayectoria con las posiciones intermedias
Move::Move(Position from, Position to, bool capture)
    : from_(from), to_(to), isCapture_(capture) {

    // Agrega la posición inicial
    path_.push_back(from);

    // Si es captura, se agrega cada celda entre 'from' y 'to'
    if (isCapture_) {
        int stepRow = (to.row - from.row) > 0 ? 1 : -1;
        int stepCol = (to.col - from.col) > 0 ? 1 : -1;

        // Recorre la diagonal entre 'from' y 'to' (sin incluir extremos)
        for (int r = from.row + stepRow, c = from.col + stepCol;
             r != to.row;
             r += stepRow, c += stepCol) {
            path_.emplace_back(Position{r, c});
        }
    }

    // Agrega la posición final
    path_.push_back(to);
}

/// Devuelve la posición inicial del movimiento
Position Move::from() const {
    return from_;
}

/// Devuelve la posición final del movimiento
Position Move::to() const {
    return to_;
}

/// Indica si el movimiento es de captura
bool Move::isCapture() const {
    return isCapture_;
}

/// Devuelve la trayectoria completa (origen, intermedios, destino)
const std::vector<Position>& Move::path() const {
    return path_;
}

/// Inserta una posición intermedia antes del destino (útil para cadenas de salto)
void Move::addToPath(const Position& pos) {
    path_.insert(path_.end() - 1, pos);
}

/// Alias de addToPath con nombre más semántico
void Move::addIntermediate(const Position& pos) {
    path_.insert(path_.end() - 1, pos);
}
