//
// Created by sashi0034 on 2022/05/21.
//

#include "TestObject.h"

namespace mainScene
{
    TestObject::TestObject(ChildrenPool<ChildBase>* belongingPool, IAppState* appState, Vec2<double> vel)
        : ChildBase(belongingPool)
    {

        m_Graph = unique_ptr<Graph>(new Graph(appState->GetRenderer(), IMG_Load("assets/dango_wolf_24x24.png")));

        m_Spr = Sprite::Create();
        m_Spr->SetTexture(SpriteTexture::Create(m_Spr, m_Graph.get()));

        m_Spr->GetTexture()->SetSrcRect(Rect<int>{0,0,24,24});

        m_Spr->SetUpdateProcess([=](IAppState* appState){
            Vec2<double> v = vel;
            m_Pos = m_Pos + v*appState->GetTime().GetDeltaSec();
            m_Spr->GetTexture()->SetPosition(m_Pos);
            m_CoroManager.UpdateEach();
            //std::cout << m_Pos.X << std::endl;
        });

        m_CoroManager.Start(new coroutine<CoroTask>::pull_type{std::bind(testCoro, std::placeholders::_1, this)});
    }

    CoroTask TestObject::testCoro(coroutine<CoroTask>::push_type &yield, TestObject *self)
    {
        for (int i = 0; i < 10; ++i)
        {
            std::cout << "coro test x: " << self->GetPos().X <<std::endl;
            yield(CoroTask(CoroTask::Result::PENDING));
        }
        return CoroTask(CoroTask::Result::SUCCESS);
    }

    const Vec2<double>& TestObject::GetPos() const
    {
        return m_Pos;
    }
}