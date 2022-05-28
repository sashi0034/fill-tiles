//
// Created by sashi0034 on 2022/05/23.
//

#include "MainRoot.h"

#include <memory>
#include "TestObject.h"
#include "BackGround.h"
#include "Player.h"

namespace mainScene{
    MainRoot::MainRoot(IAppState *appState)
    : ResImage(std::make_unique<resource::Image>(appState)), AppStatePtr(appState)
    {
        createSelfSpr();
        m_ChildrenPool.Birth(new TestObject(&m_ChildrenPool, appState, Vec2<double>{1.1, 2.2}));
        m_ChildrenPool.Birth(new TestObject(&m_ChildrenPool, appState, Vec2<double>{5.0, 8.0}));
        m_ChildrenPool.Birth(new BackGround(&m_ChildrenPool));
        m_ChildrenPool.Birth(new Player(&m_ChildrenPool));
    }

    MainRoot::~MainRoot()
    {
        m_ChildrenPool.Release();
    }

    void MainRoot::createSelfSpr()
    {
        m_Spr = Sprite::Create();
        m_Spr->SetUpdateProcess([&](IAppState*){
            m_ChildrenPool.ProcessEach([&](auto child){child->Update();});
        });
    }
}


