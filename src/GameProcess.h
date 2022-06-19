//
// Created by sashi0034 on 2022/05/04.
//

#ifndef FILL_TILES_GAMEPROCESS_H
#define FILL_TILES_GAMEPROCESS_H

#include "debug.h"

class GameProcess {
private:
#ifdef INGAME_DEBUG_FIELDVIEW
    static const int pixelPerUnit = 3;
    static const int screenWidth = 416;
    static const int screenHeight = 240;
#else
    static const int pixelPerUnit = 3;
    static const int screenWidth = 416;
    static const int screenHeight = 240;
#endif
public:
    static int RunGame();
};


#endif //FILL_TILES_GAMEPROCESS_H
