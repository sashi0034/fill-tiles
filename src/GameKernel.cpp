//
// Created by sashi0034 on 2022/05/04.
//

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <memory>
#include "GameKernel.h"
#include "mainScene/MainScene.h"
#include "gameEngine/gameEngine.h"

int GameKernel::StartGame() {

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init()<0)
    {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("KEY EVENT TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH*PIXEL_PER_UNIT,SCREEN_HEIGHT*PIXEL_PER_UNIT, SDL_WINDOW_SHOWN);
    unique_ptr<AppState> appState;

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    } else {
        appState = std::make_unique<AppState>(Vec2<int>{SCREEN_WIDTH, SCREEN_HEIGHT}, 3, window);
    }

    auto renderer = appState->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

    mainScene::MainScene::Loop(appState);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
