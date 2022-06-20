//
// Created by sashi0034 on 2022/05/23.
//

#include "GameRoot.h"

#include <memory>
#include "BackGroundTest.h"
#include "MainScene.h"
#include "FieldViewDebugScene.h"
#include "../debug.h"

namespace inGame{
    GameRoot::GameRoot(IAppState *appState)
    : ResImage(std::make_unique<resource::Image>(appState)), m_AppState(appState)
    {
        createSelfSpr();
#ifdef INGAME_DEBUG_FIELDVIEW
        m_ChildrenPool.Birth(new FieldViewDebugScene(&m_ChildrenPool, this, Vec2{0.0, 0.0}));
#else
        m_ChildrenPool.Birth(new MainScene(&m_ChildrenPool, this));
#endif
    }

    GameRoot::~GameRoot()
    {
        m_ChildrenPool.Release();
    }

    void GameRoot::createSelfSpr()
    {
        m_Spr = SpriteTexture::Create(nullptr);
        m_Spr->SetUpdateProcess([&](IAppState* app){
            m_ChildrenPool.ProcessEach([&](shared_ptr<ActorBase>& child){ child->Update(app);});
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


