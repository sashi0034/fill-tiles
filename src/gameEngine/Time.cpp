//
// Created by sashi0034 on 2022/04/29.
//

#include "Time.h"

namespace gameEngine
{
    Time::Time()
    {
        Restart();
    }

    void Time::Restart()
    {
        m_DeletaMilli = 0;
        m_DeletaSec = 0;
        m_OldTime = std::chrono::system_clock::now();
    }

    void Time::update()
    {
        auto cur = std::chrono::system_clock::now();
        auto dur = cur - m_OldTime;
        auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        m_DeletaMilli = milli;
        m_DeletaSec = milli / 1000.0;
        m_OldTime = cur;
    }

    int Time::GetDeltaMilli()
    {
        return m_DeletaMilli;
    }

    double Time::GetDeltaSec()
    {
        return m_DeletaSec;
    }

    std::unique_ptr<Fps> Time::CountFps()
    {
        m_FpsBuffur += GetDeltaMilli();
        m_FpsCount++;
        if (m_FpsBuffur > 1000)
        {
            m_FpsBuffur -= 1000;
            int ret = m_FpsCount;
            m_FpsCount = 0;
            return std::unique_ptr<Fps>(new Fps{true, ret});
        }

        return std::unique_ptr<Fps>(new Fps{false, 0});
    }
}


