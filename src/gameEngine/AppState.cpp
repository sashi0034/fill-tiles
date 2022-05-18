//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
namespace gameEngine
{
    AppState::AppState(Vec2<int> screenSize, int pixelPerUnit, unique_ptr<SDL_Renderer>& renderer)
            : m_ScreenSize(screenSize), m_PixelPerUnit(pixelPerUnit)
    {
        m_Time=unique_ptr<Time>(new Time());
        m_Renderer = std::move(renderer);
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