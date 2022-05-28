//
// Created by sashi0034 on 2022/05/28.
//

#include "Player.h"
#include "MainRoot.h"
using namespace boost::coroutines2;

namespace mainScene
{
    Player::Player(IChildrenPool<ChildBase> *belonging)
            : ChildBase(belonging),
            m_Action(coroutine<CoroTask>::pull_type{std::bind(wait, std::placeholders::_1, this)})
    {
        m_Image = MainRoot::GetInstance().ResImage->kisaragi_32x32.get();

        m_Spr = Sprite::Create();
        m_Texture = SpriteTexture::Create(m_Spr, m_Image);
        m_Spr->SetTexture(m_Texture);
        m_Texture->SetSrcRect(Rect<int>{0,0,32,32});
    }

    CoroTask Player::wait(coroutine<CoroTask>::push_type &yield, Player *self)
    {
        for (int i=0; i<256; ++i)
        {
            self->m_Pos = self->m_Pos + Vec2<double>{128.0-i, 128.0-i} *
                    MainRoot::GetInstance().AppStatePtr->GetTime().GetDeltaSec();
            yield(CoroTask::RespondPending());
        }

        return CoroTask::RespondSuccess();
    }

    void Player::Update()
    {
        if (m_Action) m_Action();
        m_Texture->SetPosition(m_Pos);
    }
}
