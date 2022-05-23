//
// Created by sashi0034 on 2022/05/21.
//

#ifndef FILL_TILES_TESTOBJECT_H
#define FILL_TILES_TESTOBJECT_H

#include "../gameEngine/gameEngine.h"

namespace mainScene
{
    class TestObject
    {
        unique_ptr<Graph> m_Graph;
        shared_ptr<Sprite> m_Spr;
        Vec2<double> m_Pos{};
    public:
        explicit TestObject(IAppState* appState, Vec2<double> vel);
    };
}

#endif //FILL_TILES_TESTOBJECT_H
