//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
namespace gameEngine
{
    AppState::AppState(Vec2<int> screenSize, int pixelPerUnit, SDL_Window* window)
            : m_ScreenSize(screenSize), m_PixelPerUnit(pixelPerUnit)
    {
        m_Time=unique_ptr<Time>(new Time());
        m_Window = unique_ptr<SDL_Window>(window);
        m_Renderer = unique_ptr<SDL_Renderer>(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
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

    const SDL_Renderer &AppState::GetRenderer() const
    {
        return *m_Renderer;
    }
}