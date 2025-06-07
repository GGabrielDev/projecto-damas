#ifndef POSITION_H
#define POSITION_H

struct Position {
    int row;
    int col;

    // Compara dos posiciones por igualdad exacta de fila y columna
    bool operator==(const Position& other) const {
        return (row == other.row) && (col == other.col);
    }
};

// Función global para validar posiciones
inline bool isValidPosition(const Position& pos) {
    return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
}

#endif // POSITION_H
