#include "GameResult.h"

const char* to_string(GameResult result) {
    switch (result) {
        case GameResult::WinWhite: return "Blanco Gana";
        case GameResult::WinBlack: return "Negro Gana";
        case GameResult::Draw: return "Empate";
        case GameResult::Ongoing: return "En juego";
        default: return "Unknown";
    }
}
