//
// Created by sashi0034 on 2022/05/04.
//

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <memory>
#include "GameTask.h"
#include "inGame/gameLooper.h"
#include "gameEngine/gameEngine.h"

int GameTask::RunGame()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() < 0)
    {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("KEY EVENT TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          screenWidth * pixelPerUnit, screenHeight * pixelPerUnit, SDL_WINDOW_SHOWN);
    unique_ptr<AppState> appState;

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } else
    {
        appState = std::make_unique<AppState>(Vec2<int>{screenWidth, screenHeight}, int(pixelPerUnit), window);
    }

    auto renderer = appState->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

    inGame::gameLooper::Loop(appState);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
