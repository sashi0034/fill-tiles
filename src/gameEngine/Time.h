//
// Created by sashi0034 on 2022/04/29.
//

#include <chrono>
#include <memory>

#ifndef FILL_TILES_TIME_H
#define FILL_TILES_TIME_H


namespace gameEngine
{
    struct Fps
    {
        bool HasValue;
        int Value;
    };

    class Time
    {
        std::chrono::system_clock::time_point m_OldTime;
        int m_DeletaMilli{};
        double m_DeletaSec{};

        int m_FpsCount;
        int m_FpsBuffur;

    public:
        Time();

        int GetDeltaMilli();

        double GetDeltaSec();

        void Restart();

        void update();

        std::unique_ptr<Fps> CountFps();
    };
}

#endif //FILL_TILES_TIME_H
