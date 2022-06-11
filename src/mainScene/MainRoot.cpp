//
// Created by sashi0034 on 2022/05/23.
//

#include "MainRoot.h"

#include <memory>
#include "BackGround.h"
#include "Player.h"
#include "AnimTest.h"

namespace mainScene{
    MainRoot::MainRoot(IAppState *appState)
    : ResImage(std::make_unique<resource::Image>(appState)), m_AppState(appState)
    {
        createSelfSpr();
        m_ChildrenPool.Birth(new BackGround(&m_ChildrenPool));
        m_ChildrenPool.Birth(new Player(&m_ChildrenPool));
        m_ChildrenPool.Birth(new AnimTest(&m_ChildrenPool));
    }

    MainRoot::~MainRoot()
    {
        m_ChildrenPool.Release();
    }

    void MainRoot::createSelfSpr()
    {
        m_Spr = SpriteTexture::Create(nullptr);
        m_Spr->SetUpdateProcess([&](IAppState* app){
            m_ChildrenPool.ProcessEach([&](auto child){ child->Update();});
            m_TextureAnimator.Update(app->GetTime().GetDeltaSec());
        });
    }

    TextureAnimator &MainRoot::GetTextureAnimator()
    {
        return m_TextureAnimator;
    }

    IAppState *MainRoot::GetAppState()
    {
        return m_AppState;
    }
}


