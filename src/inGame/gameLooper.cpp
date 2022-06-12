//
// Created by sashi0034 on 2022/05/03.
//

#include <iostream>
#include <SDL_ttf.h>
#include "gameLooper.h"
#include "MoveTest.h"
#include "FontTest.h"
#include "LibraryTest.h"
#include "../gameEngine/gameEngine.h"
#include "GameRoot.h"

void inGame::gameLooper::Loop(unique_ptr<AppState>& appState) {
    LOG_INFO << "Start Game Loop." << std::endl;

    GameRoot mainRoot(appState.get());

    do
    {
        appState->UpdateFrame();
        appState->RenderFrame();
    } while (!appState->CanQuitApp());

    LOG_INFO << "Finished Game Loop." << std::endl;
}
