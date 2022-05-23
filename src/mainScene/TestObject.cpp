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
            std::cout << m_Pos.X << std::endl;
        });
    }
}