//
// Created by sashi0034 on 2022/05/23.
//

#include "GameRoot.h"

#include <memory>
#include "BackGroundTest.h"
#include "MainScene.h"

namespace inGame{
    GameRoot::GameRoot(IAppState *appState)
    : ResImage(std::make_unique<resource::Image>(appState)), m_AppState(appState)
    {
        createSelfSpr();
        m_ChildrenPool.Birth(new MainScene(&m_ChildrenPool, this));
    }

    GameRoot::~GameRoot()
    {
        m_ChildrenPool.Release();
    }

    void GameRoot::createSelfSpr()
    {
        m_Spr = SpriteTexture::Create(nullptr);
        m_Spr->SetUpdateProcess([&](IAppState* app){
            m_ChildrenPool.ProcessEach([&](auto child){ child->Update(app);});
            m_TextureAnimator.Update(app->GetTime().GetDeltaSec());
        });
    }

    TextureAnimator &GameRoot::GetTextureAnimator()
    {
        return m_TextureAnimator;
    }

    IAppState *GameRoot::GetAppState()
    {
        return m_AppState;
    }
}


