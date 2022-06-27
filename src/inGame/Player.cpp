//
// Created by sashi0034 on 2022/05/28.
//

#include "Player.h"

#include <memory>
#include "GameRoot.h"
#include "FieldManager.h"
#include "ZIndex.h"

using namespace boost::coroutines2;

namespace inGame
{
    Player::Player(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene)
            : ActorBase(belonging), m_State(inGame::EPlayerState::Walk), m_ParentalScene(mainScene), m_Field(mainScene->GetFieldManager())
{
        m_Image = mainScene->GetRoot()->ResImage->kisaragi_32x32.get();

        initViewModel();

        initAction();
    }

    void Player::initViewModel()
    {
        m_View = std::make_unique<CharacterViewModel>(m_ParentalScene->GetScrollManager(), m_Image);
        m_View->GetView().SetSrcRect(Rect<int>{0, 0, CellSize.X, CellSize.Y});
        const double pixelPerMat = FieldManager::PixelPerMat;
        m_View->GetView().SetPosition(Vec2<double>{
                (pixelPerMat - CellSize.X) / 2.0,
                pixelPerMat - CellSize.Y} + FieldManager::CharacterPadding);
    }



    CoroTask Player::wait(CoroTaskYield &yield, Player *self, IAppState *appState)
    {
        yield();

        self->changeAnimation([&](){self->animWait(self->m_Angle);});

        EAngle goingAngle = EAngle::None;
        while (goingAngle == EAngle::None)
        {
            goingAngle = waitForWalkUntilInput(self, appState);
            yield();
        }

        self->changeStateToWalk(appState, goingAngle, true);
    }

    EAngle Player::waitForWalkUntilInput(Player *self, const IAppState *appState)
    {
        EAngle goingAngle = EAngle::None;
        auto keyState = appState->GetKeyboardState();
        auto inputAngle = getInputAngle(keyState);

        if (inputAngle!=EAngle::None)
        {
            if (self->m_Field->CanMoveTo(self->GetMatPos(), inputAngle))
                goingAngle = inputAngle;
            else if (self->m_Angle != inputAngle)
            {
                self->m_Angle = inputAngle;
                self->changeAnimation([&](){self->animWait(self->m_Angle);});
            }
        }
        return goingAngle;
    }

    void Player::Update(IAppState *appState)
    {
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

        m_PlayerAnimator.Update(appState->GetTime().GetDeltaSec());

        m_SubProcess.ProcessEach([&](ProcessTimer& process){process.Update(appState->GetTime().GetDeltaSec()); });

        ZIndexCharacter(*m_View).ApplyZ();

    }

    void Player::initAction()
    {
        IAppState* app = const_cast<IAppState*>(GameRoot::GetInstance().GetAppState());
        m_State.ChangeState(EPlayerState::Wait, new CoroTaskCall(
                std::bind(wait, std::placeholders::_1, this, app)));
    }

    CoroTask Player::walk(CoroTaskYield &yield, Player *self, IAppState *appState, EAngle goingAngle, bool canChangeAnim)
    {
        yield();

        auto moveVector = Angle(goingAngle).ToXY().CastTo<double>() * FieldManager::PixelPerMat;
        bool isDash = isDashing(appState->GetKeyboardState());
        double movingTIme = isDash ? 0.2 : 0.4;

        if (canChangeAnim)
            self->changeAnimation([&](){self->animWalk(goingAngle, isDash ? 0.5 : 1.0);});

        self->m_Angle = goingAngle;

        auto moveAnim = self->m_PlayerAnimator.TargetTo(self->m_View->GetModel().GetWeakPtr())
                ->AnimPosition(moveVector, movingTIme)->SetEase(EAnimEase::Linear)->SetRelative(true)
                ->ToWeakPtr();

        coroUtils::WaitForExpire<>(yield, moveAnim);

        self->m_OnMoveFinish.get_subscriber().on_next(self->GetMatPos());

        LOG_INFO << "Moved: " << self->GetMatPos().ToString() << std::endl;

        if (self->getInputAngle(appState->GetKeyboardState())==self->m_Angle && isDash== isDashing(appState->GetKeyboardState()))
            if (self->m_Field->CanMoveTo(self->GetMatPos(), goingAngle))
                self->changeStateToWalk(appState, goingAngle, false);

    }

    Vec2<double> Player::GetPos()
    {
        return m_View->GetModel().GetPosition();
    }

    void Player::SetPos(const Vec2<double> &pos)
    {
        LOG_INFO << "Player Position set to " << pos.ToString() << std::endl;
        m_View->GetModel().SetPosition(pos);
        m_ShouldResetScroll = true;
    }

    void Player::setPos(Vec2<double> newPos)
    {
        m_View->GetModel().SetPosition(newPos);
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
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 5}, baseTemp)->AddFrame(Vec2{1, 5}, baseTemp)->AddFrame(Vec2{2, 5}, baseTemp)->AddFrame(Vec2{3, 5}, baseTemp);
                break;
            case EAngle::Right:
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 4}, baseTemp)->AddFrame(Vec2{1, 4}, baseTemp)->AddFrame(Vec2{2, 4}, baseTemp)
                        ->AddFrame(Vec2{3, 4}, baseTemp)->AddFrame(Vec2{4, 4}, baseTemp)->AddFrame(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Left:
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 4}, baseTemp)->AddFrameFlipped(Vec2{1, 4}, baseTemp)->AddFrameFlipped(Vec2{2, 4}, baseTemp)
                        ->AddFrameFlipped(Vec2{3, 4}, baseTemp)->AddFrameFlipped(Vec2{4, 4}, baseTemp)->AddFrameFlipped(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Down:
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
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
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 2}, baseTemp)->AddFrame(Vec2{1, 2}, baseTemp)->AddFrame(Vec2{2, 2}, baseTemp)->AddFrame(Vec2{3, 2}, baseTemp);
                break;
            case EAngle::Right:
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 1}, baseTemp)->AddFrame(Vec2{1, 1}, baseTemp)->AddFrame(Vec2{2, 1}, baseTemp);
                break;
            case EAngle::Left:
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 1}, baseTemp)->AddFrameFlipped(Vec2{1, 1}, baseTemp)->AddFrameFlipped(Vec2{2, 1}, baseTemp);
                break;
            case EAngle::Down:
                m_PlayerAnimator.TargetTo(m_View->GetView().GetWeakPtr())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
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

    MatPos Player::GetMatPos()
    {
        auto pixelPos = GetPos().CastTo<int>();
        return MatPos((pixelPos + FieldManager::MatPixelSize / 2) / FieldManager::PixelPerMat);
    }

    void Player::changeAnimation(const std::function<void()>& animation)
    {
        this->m_PlayerAnimator.Release();
        animation();
    }

    rx::observable<MatPos> Player::OnMoveFinish() const
    {
        return m_OnMoveFinish.get_observable();
    }

    void Player::scrollByTracking(const Vec2<double> &trackingPos)
    {
        if (m_ParentalScene->GetFieldEventManager()->IsRunning()) return;

        auto scrollManager = m_ParentalScene->GetScrollManager();

        if (m_ShouldResetScroll)
        {
            m_ShouldResetScroll = false;
            scrollManager->SetScroll(trackingPos);
            return;
        }

        auto currPos = scrollManager->GetScroll();

        const double deltaMovingRate = 0.02;
        auto newPos = currPos * (1 - deltaMovingRate ) + trackingPos * deltaMovingRate;

        scrollManager->SetScroll(newPos);
    }

    void Player::Init()
    {
        const double fps60 = 1.0 / 60;

        m_SubProcess.Birth(new ProcessTimer([&]() {
            scrollByTracking(GetPos() * -1 +
                             (m_ParentalScene->GetRoot()->GetAppState()->GetScreenSize() /
                              2).CastTo<double>());
            return EProcessStatus::Running;
        }, fps60));

    }


}
