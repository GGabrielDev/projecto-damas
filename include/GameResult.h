#ifndef GAMERESULT_H
#define GAMERESULT_H

enum class GameResult {
    WinWhite,
    WinBlack,
    Draw,
    Ongoing
};

const char* to_string(GameResult result);

#endif // GAMERESULT_H
