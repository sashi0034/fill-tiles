//
// Created by sashi0034 on 2022/05/16.
//

#ifndef FILL_TILES_APPSTATE_H
#define FILL_TILES_APPSTATE_H

#include <SDL_image.h>
#include "Time.h"
#include "Vec2.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;


namespace gameEngine
{
    class IAppState
    {
    public:
        [[nodiscard]] virtual const Vec2<int>& GetScreenSize() const = 0;
        [[nodiscard]] virtual int GetPixelPerUnit() const = 0;
        [[nodiscard]] virtual const Time& GetTime() const = 0;
        [[nodiscard]] virtual const SDL_Renderer& GetRenderer() const = 0;
    };


    class AppState : IAppState
    {
        const Vec2<int> m_ScreenSize;
        const int m_PixelPerUnit;
        unique_ptr<Time> m_Time;
        unique_ptr<SDL_Window> m_Window;
        unique_ptr<SDL_Renderer> m_Renderer;
    public:
        AppState(Vec2<int> screenSize, int pixelPerUnit, SDL_Window* window);
        [[nodiscard]] int GetPixelPerUnit() const override;
        [[nodiscard]] const Vec2<int> & GetScreenSize() const override;
        [[nodiscard]] const Time & GetTime() const override;
        [[nodiscard]] const SDL_Renderer & GetRenderer() const override;
    };
}


#endif //FILL_TILES_APPSTATE_H
