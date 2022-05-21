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
    //auto window = &const_cast<SDL_Window&>(appState->GetWindow());
    auto renderer = &const_cast<SDL_Renderer&>(appState->GetRenderer());

    MoveTest moveTest(renderer);
    mainScene::FontTest fontTest(renderer);
    Time time{};
    LibraryTest boostTest{};

    while (1) {

        //std::cout << time.GetDeltaMilli() << std::endl;

        auto fps = time.CountFps();
        if (fps->HasValue) std::cout << "FPS: " << fps->Value << std::endl;

        SDL_RenderClear(renderer);

        moveTest.Render();
        fontTest.Render();
        SpriteTexture::RenderAll(*appState);

        SDL_RenderPresent(renderer);

        // event handling

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        if (e.type == SDL_QUIT) break;

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        moveTest.Update(time.GetDeltaMilli(), state);
        boostTest.Update();
        time.update();
        Sprite::UpdateAll(*appState);
    }
}
