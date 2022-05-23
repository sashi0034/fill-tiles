//
// Created by sashi0034 on 2022/05/23.
//

#include "MainRoot.h"
#include "TestObject.h"

namespace mainScene{
MainRoot::MainRoot(IAppState *appState)
{
    m_Children.Birth(new TestObject(&m_Children, appState, Vec2<double>{1.1, 2.2}));
    m_Children.Birth(new TestObject(&m_Children, appState, Vec2<double>{5.0, 8.0}));
}
}


