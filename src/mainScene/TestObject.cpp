//
// Created by sashi0034 on 2022/05/21.
//

#include "TestObject.h"

namespace mainScene
{
    TestObject::TestObject(AppState& appState)
    {

        m_Graph = unique_ptr<Graph>(new Graph(appState.GetRendererAsPtr(), IMG_Load("assets/dango_wolf_24x24.png")));

        m_Spr = Sprite::Create();
        m_Spr->SetTexture(SpriteTexture::Create(m_Spr, m_Graph.get()));

        m_Spr->GetTexture()->SetSrcRect(Rect<int>{0,0,24,24});

        m_Spr->SetUpdateProcess([this](AppState& app){
            m_Pos = m_Pos + Vec2<double>{0.01, 0.01};
            m_Spr->GetTexture()->SetPosition(m_Pos);
        });
    }
}