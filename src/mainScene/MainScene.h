//
// Created by sashi0034 on 2022/05/03.
//

#ifndef FILL_TILES_MAINSCENE_H
#define FILL_TILES_MAINSCENE_H

#include <SDL.h>
#include <SDL_image.h>

namespace mainScene {
    class MainScene {

    public:
        static void Loop(SDL_Window *window, SDL_Renderer *renderer);
    };
}


#endif //FILL_TILES_MAINSCENE_H
