//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
namespace gameEngine
{
    AppState::AppState(Vec2<int> screenSize, int pixelPerUnit)
            : m_ScreenSize(screenSize), m_PixelPerUnit(pixelPerUnit)
    {
        m_Time=unique_ptr<Time>(new Time());
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
}