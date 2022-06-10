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

    CoroTask Player::wait(CoroTaskYield &yield, Player *self, IAppState *appState)
    {
        EAngle goingAngle = EAngle::None;
        while (goingAngle == EAngle::None)
        {
            yield();
            auto keyState = appState->GetKeyboardState();
            if (keyState== nullptr) continue;
            if (keyState[SDL_Scancode::SDL_SCANCODE_W]) goingAngle = EAngle::Up;
            if (keyState[SDL_Scancode::SDL_SCANCODE_A]) goingAngle = EAngle::Left;
            if (keyState[SDL_Scancode::SDL_SCANCODE_S]) goingAngle = EAngle::Down;
            if (keyState[SDL_Scancode::SDL_SCANCODE_D]) goingAngle = EAngle::Right;
        }

        self->m_State.ChangeState(EPlayerState::Walk,
                                  new CoroTaskCall(std::bind(walk, std::placeholders::_1, self, goingAngle)));

    }

    void Player::Update()
    {
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

        m_PlayerAnimator.Update(MainRoot::GetInstance().AppStatePtr->GetTime().GetDeltaSec());
    }

    void Player::initAction()
    {
        IAppState* app = const_cast<IAppState*>(MainRoot::GetInstance().AppStatePtr);
        m_State.ChangeState(EPlayerState::Wait, new CoroTaskCall(
                std::bind(wait, std::placeholders::_1, this, app)));
    }

    CoroTask Player::walk(CoroTaskYield &yield, Player *self, EAngle goingAngle)
    {
        auto moveVector = Angle(goingAngle).ToXY().EachTo<double>() * 16;

        auto moveAnim = self->m_PlayerAnimator.TargetTo(self->m_ViewModelTexture)
            ->AnimPosition(moveVector, 0.5)->SetEase(EAnimEase::Linear)->SetRelative(true)
            ->GetWeakPtr();

        coroUtils::WaitForExpire<>(yield, moveAnim);
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
