//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
#include "../gameEngine/SpriteTexture.h"
#include <memory>
#include <iostream>

namespace gameEngine
{

    AppState::AppState()
    {}

    AppState::AppState(const Vec2<int> &screenSize, const int pixelPerUnit, SDL_Window* window)
        : m_ScreenSize(screenSize), m_PixelPerUnit(pixelPerUnit)
    {
        m_Time = std::make_unique<Time>();
        m_Window = window;
        m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    int AppState::GetPixelPerUnit() const
    {
        return m_PixelPerUnit;
    }

    Vec2<int> AppState::GetScreenSize() const
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

        int w, h;
        SDL_GetWindowSize(m_Window, &w, &h);
        m_ScreenSize = Vec2{w/m_PixelPerUnit, h/m_PixelPerUnit};

        m_KeyboardState = SDL_GetKeyboardState(NULL);
        m_Time->Update(true);
        SpriteTexture::UpdateAll(this);
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
            processEvent(e);
    }

    void AppState::processEvent(SDL_Event &e)
    {
        switch (e.type)
        {
            case SDL_QUIT:
                m_CanQuitApp = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_Mouse.SetPushed(e.button.button, true);
                break;
            case SDL_MOUSEBUTTONUP:
                m_Mouse.SetPushed(e.button.button, false);
                break;
            case SDL_MOUSEMOTION:
                m_Mouse.SetPosition(Vec2<double>(double(e.motion.x), double(e.motion.y)) / m_PixelPerUnit);
                break;
            case SDL_WINDOWEVENT_RESIZED:
                // SDL2???????????????????????????????????????
                std::cout << e.window.data1 << ", " << e.window.data2 << std::endl;
                assert(false);
                break;
            default:
                break;
        }
    }

    bool AppState::CanQuitApp() const
    {
        return m_CanQuitApp;
    }

    const IMouseState *AppState::GetMouseState() const
    {
        return &m_Mouse;
    }

}