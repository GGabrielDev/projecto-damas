#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "GameResult.h"

class FileManager {
public:
    void saveResult(const GameResult& result);
};

#endif // FILEMANAGER_H
