#ifndef GAMERESULT_H
#define GAMERESULT_H

/// Posibles estados de una partida.
enum class GameResult {
    WinWhite,   // Blancas ganan
    WinBlack,   // Negras ganan
    Draw,       // Empate
    Ongoing     // La partida continúa
};

// Convierte GameResult a string legible
const char* to_string(GameResult result);

#endif // GAMERESULT_H
