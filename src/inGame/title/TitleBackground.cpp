//
// Created by sashi0034 on 2022/08/25.
//

#include "TitleBackground.h"
#include "MenuScene.h"
#include "../GameRoot.h"

namespace inGame::title
{
    TitleBackground::TitleBackground(MenuScene *menuScene) :
        ActorBase(menuScene->GetChildren()),
        menuScene(menuScene),
        _bgChip(menuScene->RootRef->RscImage->title_bg_chip.get())
    {
        _texture.SetRenderingProcess([this](IAppState* app){ render(app);});
    }

    void TitleBackground::render(IAppState *app)
    {
        const auto screenSize = app->GetRealScreenSize();
        const auto chipSize = _bgChip->GetSize();

        for (int x=-(screenSize.X % chipSize.X)/2; x<screenSize.X; x+=chipSize.X)
        {
            for (int y=0; y<screenSize.Y; y+=chipSize.Y)
            {
                _bgChip->RenderGraph(
                        app->GetRenderer(),
                        Vec2{x, y},
                        Rect{Vec2{0, 0}, chipSize},
                        Vec2{1.0, 1.0});
            }
        }
    }
} // inGame