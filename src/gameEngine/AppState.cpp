//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
#include <memory>

namespace gameEngine
{

    AppState::AppState()
    {}

    AppState::AppState(Vec2<int> screenSize, int pixelPerUnit, SDL_Window* window)
            : m_ScreenSize(screenSize), m_PixelPerUnit(pixelPerUnit)
    {
        m_Time=std::make_unique<Time>();
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

    AppState::~AppState() = default;

}