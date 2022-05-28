//
// Created by sashi0034 on 2022/05/23.
//

#include "MainRoot.h"

#include <memory>
#include "TestObject.h"
#include "BackGround.h"

namespace mainScene{
    MainRoot::MainRoot(IAppState *appState)
    : ResImage(std::make_unique<resource::Image>(appState)), AppStatePtr(appState)
    {
        m_Children.Birth(new TestObject(&m_Children, appState, Vec2<double>{1.1, 2.2}));
        m_Children.Birth(new TestObject(&m_Children, appState, Vec2<double>{5.0, 8.0}));
        m_Children.Birth(new BackGround(&m_Children));
    }

    MainRoot::~MainRoot()
    {
        m_Children.Release();
    }
}


