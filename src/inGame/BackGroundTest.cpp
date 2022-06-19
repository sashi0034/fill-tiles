//
// Created by sashi0034 on 2022/05/28.
//

#include "BackGroundTest.h"
#include "GameRoot.h"
namespace inGame{

    BackGroundTest::BackGroundTest(IChildrenPool<ActorBase> *belongingPool)
    : ActorBase(belongingPool)
    {
        (void)belongingPool;

        m_Spr = SpriteTexture::Create(nullptr);
        m_Spr->SetZ(1000);
        m_Spr->SetRenderingProcess([this](IAppState* app){ render(app);});
    }

    void BackGroundTest::render(IAppState *appState)
    {
        const int tileSize = 32;
        for (int x=0; x<appState->GetScreenSize().X; x+=tileSize)
            for (int y = 0; y <appState->GetScreenSize().Y ; y+=tileSize)
            {
                GameRoot::GetInstance().ResImage->test_room_floor_32x32->RenderGraph(
                        appState->GetRenderer(), Vec2<int>{x, y}*appState->GetPixelPerUnit(), Rect<int>{0, 0, 32, 32},  Vec2<double>{1, 1}*appState->GetPixelPerUnit()
                        );
            }
    }
}