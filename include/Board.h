#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Piece.h"
#include "Move.h"
#include "Position.h"

class Board {
public:
    Board();                                // Constructor por defecto: inicializa el tablero vacío
    Board(const Board& other);              // Constructor de copia profunda
    Board& operator=(const Board& other);   // Operador de asignación profunda
    ~Board();                               // Destructor: limpia memoria

    void clear();                           // Libera toda la memoria de piezas en el tablero
    void initialize();                      // Coloca las piezas en las posiciones iniciales estándar

    void placePiece(const Position& pos, Piece* piece);  // Coloca (y sobreescribe) una pieza en una celda
    bool isEmpty(const Position& pos) const;             // Verifica si una celda está vacía
    Piece* getPiece(const Position& pos) const;          // Obtiene un puntero a la pieza en esa celda

    void movePiece(const Position& from, const Position& to);  // Mueve una pieza y aplica ascenso si corresponde
    void removePiece(const Position& pos);                     // Elimina una pieza (libera memoria)
    void print() const;                                        // Imprime el tablero a consola (modo debug)
    int countPieces(Color color) const;                        // Cuenta la cantidad de piezas de cierto color

private:
    std::array<std::array<Piece*, 8>, 8> squares_;  // Matriz 8x8 de punteros a piezas (nullptr si vacío)
};

#endif // BOARD_H
