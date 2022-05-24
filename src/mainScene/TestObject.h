//
// Created by sashi0034 on 2022/05/21.
//

#ifndef FILL_TILES_TESTOBJECT_H
#define FILL_TILES_TESTOBJECT_H

#include "../gameEngine/gameEngine.h"
#include "../gameEngine/ChildBase.h"
#include <boost/coroutine2/coroutine.hpp>

using namespace boost::coroutines2;

namespace mainScene
{
    class TestObject : public ChildBase
    {
    public:
        explicit TestObject(ChildrenPool<ChildBase>* belongingPool, IAppState* appState, Vec2<double> vel);
        const Vec2<double>& GetPos() const;
    private:
        unique_ptr<Graph> m_Graph;
        shared_ptr<Sprite> m_Spr;
        Vec2<double> m_Pos{};
        CoroutineManager m_CoroManager{};
        static CoroTask testCoro(coroutine<CoroTask>::push_type &yield, TestObject* self);
    };
}

#endif //FILL_TILES_TESTOBJECT_H
