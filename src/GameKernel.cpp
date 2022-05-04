//
// Created by sashi0034 on 2022/05/04.
//

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "GameKernel.h"
#include "MainScene.h"

int GameKernel::StartGame() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init()<0)
    {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
    }

    window = SDL_CreateWindow("KEY EVENT TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

    MainScene::Loop(window, renderer);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
