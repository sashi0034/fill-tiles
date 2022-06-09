//
// Created by sashi0034 on 2022/05/28.
//

#include "Player.h"

#include <memory>
#include "MainRoot.h"
using namespace boost::coroutines2;

namespace mainScene
{
    Player::Player(IChildrenPool<ChildBase> *belonging)
            : ChildBase(belonging), m_State(mainScene::EPlayerState::Walk)
    {
        m_Image = MainRoot::GetInstance().ResImage->kisaragi_32x32.get();

        m_Spr = Sprite::Create();
        m_Texture = SpriteTexture::Create(m_Spr, m_Image);
        m_Spr->SetTexture(m_Texture);
        m_Texture->SetSrcRect(Rect<int>{0,0,32,32});

        initAction();
    }

    // todo: プレイヤー処理を移動
    CoroTask Player::wait(CoroTaskYield &yield, Player *self)
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
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

        m_Texture->SetPosition(m_Pos);
    }

    void Player::initAction()
    {
        m_State.ChangeState(EPlayerState::Wait, new CoroTaskCall(std::bind(wait, std::placeholders::_1, this)));
    }

    CoroTask Player::walk(CoroTaskYield &yield, Player *self)
    {
        (void) yield;
        (void)self;

        return CoroTask(CoroTask::Result::Success);
    }
}
