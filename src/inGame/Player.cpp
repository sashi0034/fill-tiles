//
// Created by sashi0034 on 2022/05/28.
//

#include "Player.h"

#include <memory>
#include "GameRoot.h"
#include "FieldManager.h"

using namespace boost::coroutines2;

namespace inGame
{
    Player::Player(IChildrenPool<ActorBase> *belonging)
            : ActorBase(belonging), m_State(inGame::EPlayerState::Walk)
    {
        m_Image = GameRoot::GetInstance().ResImage->kisaragi_32x32.get();

        initViewModel();
        initView();

        initAction();
    }

    void Player::initViewModel()
    {
        m_ViewModelTexture = SpriteTexture::Create(nullptr);
    }

    void Player::initView()
    {
        m_ViewTexture = SpriteTexture::Create(m_Image);
        m_ViewTexture->SetSrcRect(Rect<int>{0, 0, CellSize.X, CellSize.Y});
        m_ViewTexture->SetPositionParent(m_ViewModelTexture);
    }

    CoroTask Player::wait(CoroTaskYield &yield, Player *self, IAppState *appState)
    {
        yield();

        self->m_PlayerAnimator.Release();
        self->animWait(self->m_Angle);

        EAngle goingAngle = EAngle::None;
        while (goingAngle == EAngle::None)
        {
            auto keyState = appState->GetKeyboardState();
            goingAngle = getInputAngle(keyState);
            yield();
        }

        self->changeStateToWalk(appState, goingAngle, true);

    }

    void Player::Update(IAppState *appState)
    {
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

        m_PlayerAnimator.Update(appState->GetTime().GetDeltaSec());
    }

    void Player::initAction()
    {
        IAppState* app = const_cast<IAppState*>(GameRoot::GetInstance().GetAppState());
        m_State.ChangeState(EPlayerState::Wait, new CoroTaskCall(
                std::bind(wait, std::placeholders::_1, this, app)));
    }

    void Player::walk(CoroTaskYield &yield, Player *self, IAppState *appState, EAngle goingAngle, bool canChangeAnim)
    {
        yield();

        auto moveVector = Angle(goingAngle).ToXY().EachTo<double>() * FieldManager::PixelPerUnit;
        bool isDash = isDashing(appState->GetKeyboardState());
        double movingTIme = isDash ? 0.2 : 0.4;

        if (canChangeAnim){
            self->m_PlayerAnimator.Release();
            self->animWalk(goingAngle, isDash ? 0.5 : 1.0);
        }

        self->m_Angle = goingAngle;

        auto moveAnim = self->m_PlayerAnimator.TargetTo(self->m_ViewModelTexture)
            ->AnimPosition(moveVector, movingTIme)->SetEase(EAnimEase::Linear)->SetRelative(true)
            ->GetWeakPtr();

        coroUtils::WaitForExpire<>(yield, moveAnim);

        if (self->getInputAngle(appState->GetKeyboardState())==self->m_Angle && isDash== isDashing(appState->GetKeyboardState()))
            self->changeStateToWalk(appState, goingAngle, false);

    }

    Vec2<double> Player::GetPos()
    {
        return m_ViewTexture->GetPosition();
    }

    void Player::setPos(Vec2<double> newPos)
    {
        m_ViewTexture->SetPosition(newPos);
    }

    bool Player::isDashing(const Uint8 *keyState)
    {
        const auto dashKey = SDL_Scancode ::SDL_SCANCODE_LSHIFT;
        return keyState[dashKey];
    }

    void Player::animWalk(EAngle angle, double frameSpeed)
    {
        const Vec2<int>& cellSize = CellSize;
        const double baseTemp = 0.2 * frameSpeed;

        switch (angle)
        {
            case EAngle::Up:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 5}, baseTemp)->AddFrame(Vec2{1, 5}, baseTemp)->AddFrame(Vec2{2, 5}, baseTemp)->AddFrame(Vec2{3, 5}, baseTemp);
                break;
            case EAngle::Right:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 4}, baseTemp)->AddFrame(Vec2{1, 4}, baseTemp)->AddFrame(Vec2{2, 4}, baseTemp*1.5)
                        ->AddFrame(Vec2{3, 4}, baseTemp)->AddFrame(Vec2{4, 4}, baseTemp)->AddFrame(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Left:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 4}, baseTemp)->AddFrameFlipped(Vec2{1, 4}, baseTemp)->AddFrameFlipped(Vec2{2, 4}, baseTemp*1.5)
                        ->AddFrameFlipped(Vec2{3, 4}, baseTemp)->AddFrameFlipped(Vec2{4, 4}, baseTemp)->AddFrameFlipped(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Down:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 3}, baseTemp)->AddFrame(Vec2{1, 3}, baseTemp)->AddFrame(Vec2{2, 3}, baseTemp)->AddFrame(Vec2{3, 3}, baseTemp);
                break;
            default:
                assert(false);
        }
    }

    void Player::animWait(EAngle angle)
    {
        const Vec2<int>& cellSize = CellSize;
        const double baseTemp = 0.25;

        switch (angle)
        {
            case EAngle::Up:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 2}, baseTemp)->AddFrame(Vec2{1, 2}, baseTemp)->AddFrame(Vec2{2, 2}, baseTemp)->AddFrame(Vec2{3, 2}, baseTemp);
                break;
            case EAngle::Right:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 1}, baseTemp)->AddFrame(Vec2{1, 1}, baseTemp)->AddFrame(Vec2{2, 1}, baseTemp);
                break;
            case EAngle::Left:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 1}, baseTemp)->AddFrameFlipped(Vec2{1, 1}, baseTemp)->AddFrameFlipped(Vec2{2, 1}, baseTemp);
                break;
            case EAngle::Down:
                m_PlayerAnimator.TargetTo(m_ViewTexture)->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 0}, baseTemp)->AddFrame(Vec2{1, 0}, baseTemp)->AddFrame(Vec2{2, 0}, baseTemp)->AddFrame(Vec2{3, 0}, baseTemp);
                break;
            default:
                assert(false);
        }
    }

    EAngle Player::getInputAngle(const Uint8 *keyState)
    {
        if (keyState[SDL_Scancode::SDL_SCANCODE_W]) return EAngle::Up;
        if (keyState[SDL_Scancode::SDL_SCANCODE_A]) return EAngle::Left;
        if (keyState[SDL_Scancode::SDL_SCANCODE_S]) return EAngle::Down;
        if (keyState[SDL_Scancode::SDL_SCANCODE_D]) return EAngle::Right;
        return EAngle::None;
    }

    void Player::changeStateToWalk(IAppState *appState, EAngle newAngle, bool canChangeAnim)
    {
        m_State.ChangeState(EPlayerState::Walk,
                                  new CoroTaskCall(std::bind(walk, std::placeholders::_1, this, appState, newAngle, canChangeAnim)));
    }


}
