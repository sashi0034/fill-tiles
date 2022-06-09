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

        initViewModel();
        initView();

        initAction();
    }

    void Player::initViewModel()
    {
        m_ViewModelSprite = Sprite::Create();
        m_ViewModelTexture = SpriteTexture::Create(m_ViewModelSprite, nullptr);
        m_ViewModelSprite->SetTexture(m_ViewModelTexture);
    }

    void Player::initView()
    {
        m_ViewSprite = Sprite::Create();
        m_ViewTexture = SpriteTexture::Create(m_ViewSprite, m_Image);
        m_ViewSprite->SetTexture(m_ViewTexture);
        m_ViewTexture->SetSrcRect(Rect<int>{0, 0, 32, 32});
        m_ViewTexture->SetPositionParent(m_ViewModelSprite->GetTexture());
    }

    // todo: プレイヤー処理を移動
    CoroTask Player::wait(CoroTaskYield &yield, Player *self)
    {
        for (int i=0; i<256; ++i)
        {
            auto newPos = self->GetPos() + Vec2<double>{128.0-i, 128.0-i} *
                    MainRoot::GetInstance().AppStatePtr->GetTime().GetDeltaSec();
            self->setPos(newPos);

            yield(CoroTask::RespondPending());
        }

        return CoroTask::RespondSuccess();
    }

    void Player::Update()
    {
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

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

    Vec2<double> Player::GetPos()
    {
        return m_ViewTexture->GetPosition();
    }

    void Player::setPos(Vec2<double> newPos)
    {
        m_ViewTexture->SetPosition(newPos);
    }

}
