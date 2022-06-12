//
// Created by sashi0034 on 2022/06/12.
//

#include "MainScene.h"

#include <memory>
#include "BackGround.h"
#include "Player.h"
#include "AnimTest.h"
#include "TileMap.h"

namespace inGame{
    MainScene::MainScene(IAppState *appState, IChildrenPool<ActorBase> *parent)
            : ActorBase(parent),
            ResImage(std::make_unique<resource::Image>(appState))
    {
        m_ChildrenPool.Birth(new BackGround(&m_ChildrenPool));
        m_ChildrenPool.Birth(new Player(&m_ChildrenPool));
        m_ChildrenPool.Birth(new AnimTest(&m_ChildrenPool));
    }

    MainScene::~MainScene()
    {
        m_ChildrenPool.Release();
    }

    TextureAnimator &MainScene::GetTextureAnimator()
    {
        return m_TextureAnimator;
    }

    void MainScene::Update(IAppState* appState)
    {
        m_ChildrenPool.ProcessEach([&](auto child){ child->Update(appState);});
        m_TextureAnimator.Update(appState->GetTime().GetDeltaSec());
    }

}


