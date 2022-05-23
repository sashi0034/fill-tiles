//
// Created by sashi0034 on 2022/05/03.
//

#include <iostream>
#include <SDL_ttf.h>
#include "MainScene.h"
#include "MoveTest.h"
#include "../Time.h"
#include "FontTest.h"
#include "LibraryTest.h"
#include "../gameEngine/gameEngine.h"
#include "TestObject.h"

void mainScene::MainScene::Loop(unique_ptr<AppState>& appState) {
    std::cout << "Start Main Scene" << std::endl;

    unique_ptr<TestObject> test1(new TestObject(appState.get(), Vec2<double>{5, 5}));
    unique_ptr<TestObject> test2(new TestObject(appState.get(), Vec2<double>{10, 3}));

    do
    {
        appState->UpdateFrame();
        appState->RenderFrame();
    } while (!appState->CanQuitApp());
}
