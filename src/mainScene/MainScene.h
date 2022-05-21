//
// Created by sashi0034 on 2022/05/03.
//

#ifndef FILL_TILES_MAINSCENE_H
#define FILL_TILES_MAINSCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include "../gameEngine/gameEngine.h"

namespace mainScene {
    class MainScene {

    public:
        static void Loop(unique_ptr<AppState>& appState);
    };
}


#endif //FILL_TILES_MAINSCENE_H
