//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
#include <memory>
#include "Sprite.h"

namespace gameEngine
{

    AppState::AppState()
    {}

    AppState::AppState(Vec2<int> screenSize, int pixelPerUnit, SDL_Window* window)
        : IAppState(), m_ScreenSize(screenSize), m_PixelPerUnit(pixelPerUnit)
    {
        m_Time = std::make_unique<Time>();
        m_Window = window;
        m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    int AppState::GetPixelPerUnit() const
    {
        return m_PixelPerUnit;
    }

    const Vec2<int> &AppState::GetScreenSize() const
    {
        return m_ScreenSize;
    }

    const Time &AppState::GetTime() const
    {
        return *m_Time;
    }
    SDL_Window *AppState::GetWindow() const
    {
        return m_Window;
    }

    SDL_Renderer *AppState::GetRenderer() const
    {
        return m_Renderer;
    }

    void AppState::UpdateFrame()
    {
        pollEvent();
        m_KeyboardState = SDL_GetKeyboardState(NULL);
        m_Time->Update();
        Sprite::UpdateAll(this);
    }

    void AppState::RenderFrame()
    {
        SDL_RenderClear(m_Renderer);

        SpriteTexture::RenderAll(this);

        SDL_RenderPresent(m_Renderer);
    }

    const Uint8 *AppState::GetKeyboardState() const
    {
        return m_KeyboardState;
    }

    void AppState::pollEvent()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                m_CanQuitApp = true;
        }
    }

    bool AppState::CanQuitApp() const
    {
        return m_CanQuitApp;
    }

    AppState::~AppState() = default;

}