//
// Created by sashi0034 on 2022/05/03.
//

#include <iostream>
#include <SDL_ttf.h>
#include "MainScene.h"
#include "MoveTest.h"
#include "FontTest.h"
#include "LibraryTest.h"
#include "../gameEngine/gameEngine.h"
#include "TestObject.h"
#include "MainRoot.h"

void mainScene::MainScene::Loop(unique_ptr<AppState>& appState) {
    std::cout << "Start Main Scene" << std::endl;

    MainRoot mainRoot(appState.get());

    do
    {
        appState->UpdateFrame();
        appState->RenderFrame();
    } while (!appState->CanQuitApp());
}
