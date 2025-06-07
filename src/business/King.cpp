#include "King.h"
#include "Board.h"
#include "Move.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

King::King(Color color) : Piece(color, PieceType::King) {}

static void exploreKingCaptures(const Board& board, const Position& from, Color color,
                                std::vector<Position> path, std::set<Position> captured,
                                std::vector<Move>& captures) {
    bool found = false;

    // Explora las 4 diagonales
    for (int dr : {-1, 1}) {
        for (int dc : {-1, 1}) {
            int r = from.row + dr;
            int c = from.col + dc;
            bool enemyFound = false;
            Position enemyPos{-1, -1};

            // Avanza mientras esté dentro del tablero
            while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                Position current{r, c};
                if (board.isEmpty(current)) {
                    if (enemyFound) {
                        // Captura válida, avanzar
                        if (std::find(path.begin(), path.end(), current) == path.end()) {
                            Board nextBoard = board;
                            nextBoard.removePiece(enemyPos);
                            nextBoard.movePiece(from, current);

                            std::vector<Position> newPath = path;
                            newPath.push_back(current);

                            std::set<Position> newCaptured = captured;
                            newCaptured.insert(enemyPos);

                            exploreKingCaptures(nextBoard, current, color, newPath, newCaptured, captures);
                            found = true;
                        }
                    }
                    r += dr;
                    c += dc;
                } else {
                    Piece* p = board.getPiece(current);
                    if (p->color() == color || enemyFound) {
                        break;  // Obstáculo o ya vimos un enemigo
                    } else {
                        // Primer enemigo en la ruta
                        if (captured.count(current)) break;  // No repetir
                        enemyFound = true;
                        enemyPos = current;
                        r += dr;
                        c += dc;
                    }
                }
            }
        }
    }

    // Si no hubo más capturas pero hay una ruta válida
    if (!found && path.size() > 1) {
        Move m(path.front(), path.back(), true);
        for (size_t i = 1; i < path.size() - 1; ++i) {
            m.addIntermediate(path[i]);
        }

        std::cout << "[DEBUG] King Capture added with path: ";
        for (const auto& p : m.path()) {
            std::cout << "(" << p.row << "," << p.col << ") ";
        }
        std::cout << "\n";

        captures.push_back(m);
    }
}

std::vector<Move> King::validMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;

    // Primero: agregar movimientos simples en 4 diagonales
    for (int dr : {-1, 1}) {
        for (int dc : {-1, 1}) {
            Position to{from.row + dr, from.col + dc};
            if (isValidPosition(to) && board.isEmpty(to)) {
                moves.emplace_back(from, to, false);
            }
        }
    }

    // Luego: si hay enemigos cerca, intentar capturas
    bool hasEnemies = false;
    for (int dr : {-1, 1}) {
        for (int dc : {-1, 1}) {
            Position check{from.row + dr, from.col + dc};
            if (isValidPosition(check)) {
                const Piece* p = board.getPiece(check);
                if (p && p->color() != color()) {
                    hasEnemies = true;
                    break;
                }
            }
        }
        if (hasEnemies) break;
    }

    if (hasEnemies) {
        std::vector<Move> captures;
        std::vector<Position> path = {from};
        std::set<Position> captured;
        exploreKingCaptures(board, from, color(), path, captured, captures);
        if (!captures.empty()) return captures; // Reemplaza movimientos simples si hay capturas
    }

    return moves;
}
