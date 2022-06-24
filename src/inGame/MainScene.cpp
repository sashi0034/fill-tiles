//
// Created by sashi0034 on 2022/06/12.
//

#include "MainScene.h"

#include <memory>
#include "Player.h"
#include "AnimTest.h"
#include "field/TileMap.h"
#include "GameRoot.h"
#include "MineFlowerManager.h"

namespace inGame{
    MainScene::MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root)
            : ActorBase(parent), m_Root(root)
    {
        m_ScrollManager = std::make_unique<ScrollManager>(this);

        m_FieldManager = m_ChildrenPool.BirthAs<FieldManager>(new FieldManager(&m_ChildrenPool, this));

        m_Player = m_ChildrenPool.BirthAs<Player>(new Player(&m_ChildrenPool, this));

        m_ChildrenPool.Birth(new MineFlowerManager(&m_ChildrenPool, this));

        init();
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
        m_ChildrenPool.ProcessEach([&](auto& child){ child.Update(appState);});

        m_TextureAnimator.Update(appState->GetTime().GetDeltaSec());
    }

    GameRoot *MainScene::GetRoot()
    {
        return m_Root;
    }

    IFieldManager* MainScene::GetFieldManager()
    {
        return m_FieldManager;
    }

    ScrollManager *MainScene::GetScrollManager()
    {
        return m_ScrollManager.get();
    }

    void MainScene::init()
    {
        m_ChildrenPool.ProcessEach([&](auto& child){ child.Init();});
    }

    Player *MainScene::GetPlayer()
    {
        return m_Player;
    }

}


