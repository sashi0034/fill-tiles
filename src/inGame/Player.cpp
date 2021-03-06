//
// Created by sashi0034 on 2022/05/28.
//

#include "Player.h"

#include <memory>
#include "GameRoot.h"
#include "FieldManager.h"
#include "ZIndex.h"
#include "PlayerMoveData.h"
#include "character/Catfish.h"

using namespace boost::coroutines2;

namespace inGame
{
    Player::Player(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene)
            : ActorBase(belonging), m_State(inGame::EPlayerState::Walk), m_ParentalScene(mainScene), m_Field(mainScene->GetFieldManager())
{
        m_Image = mainScene->GetRoot()->RscImage->kisaragi_32x32.get();

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

        // フィールド上でイベントが発生していたら待機する
        self->waitFieldEvent(yield);

        EAngle goingAngle = EAngle::None;
        while (goingAngle == EAngle::None)
        {
            goingAngle = self->tryWalkOrActionByInput(yield, appState);

            yield();
        }

        self->changeStateToWalk(appState, goingAngle, true);
    }

    void Player::waitFieldEvent(CoroTaskYield &yield)
    {
        coroUtil::WaitForTrue(yield, [this](){return !this->isRunningFieldEvent();});
    }

    EAngle Player::tryWalkOrActionByInput(CoroTaskYield &yield, const IAppState *appState)
    {
        EAngle goingAngle = EAngle::None;
        auto keyState = appState->GetKeyboardState();
        auto inputAngle = getInputAngle(keyState);

        if (inputAngle!=EAngle::None)
        {
            auto checkingMove = this->m_Field->CheckMoveTo(this->GetMatPos(), inputAngle);

            if (checkingMove.CanMove)
                goingAngle = inputAngle;
            else if (this->m_Angle != inputAngle)
            {
                this->m_Angle = inputAngle;
                this->changeAnimation([&](){this->animWait(this->m_Angle);});
            }

            auto collidedObject = checkingMove.CollidedObject;

            if (auto catfish = dynamic_cast<character::Catfish*>(collidedObject))
                pushCatfish(yield, inputAngle, catfish);

        }
        return goingAngle;
    }

    void Player::pushCatfish(CoroTaskYield &yield, EAngle &inputAngle, character::Catfish *catfish)
    {
        bool result = catfish->TryMove(inputAngle);
        if (!result) return;

        waitFieldEvent(yield);

        PlayerActionPushCatfish action(catfish);
        m_OnAction.get_subscriber().on_next(&action);
        waitFieldEvent(yield);
    }


    void Player::Update(IAppState *appState)
    {
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

        m_SubProcess.ProcessEach([&](ProcessTimer& process){process.Update(appState->GetTime().GetDeltaSec()); });

        m_PlayerAnimator.Update(appState->GetTime().GetDeltaSec());


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

        PlayerMoveData moveData(
            self->GetMatPos(),
            self->GetMatPos() +  MatPos(Angle(self->m_Angle).ToXY()),
            self->m_Angle,
            isDash);

        // 移動開始時のフィールドイベントを発火
        self->m_OnMoveBegin.get_subscriber().on_next(&moveData);

        // 歩行アニメーション
        auto moveAnim = self->m_PlayerAnimator.TargetTo(self->m_View->GetModel())
                ->AnimPosition(moveVector, movingTIme)->SetEase(EAnimEase::Linear)->SetRelative(true)
                ->ToWeakPtr();

        coroUtil::WaitForExpire<>(yield, moveAnim);

        // 移動終了時のフィールドイベントを発火
        self->m_OnMoveFinish.get_subscriber().on_next(&moveData);

        // フィールドイベントが発生したら待機にする
        if (self->isRunningFieldEvent()) return;

        //LOG_INFO << "Moved: " << self->GetMatPos().ToString() << std::endl;

        if (self->getInputAngle(appState->GetKeyboardState())==self->m_Angle && isDash== isDashing(appState->GetKeyboardState()))
            if (self->m_Field->CheckMoveTo(self->GetMatPos(), goingAngle).CanMove)
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
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 5}, baseTemp)->AddFrame(Vec2{1, 5}, baseTemp)->AddFrame(Vec2{2, 5}, baseTemp)->AddFrame(Vec2{3, 5}, baseTemp);
                break;
            case EAngle::Right:
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 4}, baseTemp)->AddFrame(Vec2{1, 4}, baseTemp)->AddFrame(Vec2{2, 4}, baseTemp)
                        ->AddFrame(Vec2{3, 4}, baseTemp)->AddFrame(Vec2{4, 4}, baseTemp)->AddFrame(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Left:
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 4}, baseTemp)->AddFrameFlipped(Vec2{1, 4}, baseTemp)->AddFrameFlipped(Vec2{2, 4}, baseTemp)
                        ->AddFrameFlipped(Vec2{3, 4}, baseTemp)->AddFrameFlipped(Vec2{4, 4}, baseTemp)->AddFrameFlipped(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Down:
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
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
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 2}, baseTemp)->AddFrame(Vec2{1, 2}, baseTemp)->AddFrame(Vec2{2, 2}, baseTemp)->AddFrame(Vec2{3, 2}, baseTemp);
                break;
            case EAngle::Right:
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 1}, baseTemp)->AddFrame(Vec2{1, 1}, baseTemp)->AddFrame(Vec2{2, 1}, baseTemp)
                        ->AddFrame(Vec2{0, 1}, baseTemp)->AddFrame(Vec2{1, 1}, baseTemp)->AddFrame(Vec2{2, 1}, baseTemp)
                        ->AddFrame(Vec2{3, 1}, baseTemp);
                break;
            case EAngle::Left:
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 1}, baseTemp)->AddFrameFlipped(Vec2{1, 1}, baseTemp)->AddFrameFlipped(Vec2{2, 1}, baseTemp)
                        ->AddFrameFlipped(Vec2{0, 1}, baseTemp)->AddFrameFlipped(Vec2{1, 1}, baseTemp)->AddFrameFlipped(Vec2{2, 1}, baseTemp)
                        ->AddFrameFlipped(Vec2{3, 1}, baseTemp);
                break;
            case EAngle::Down:
                m_PlayerAnimator.TargetTo(m_View->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 0}, baseTemp)->AddFrame(Vec2{1, 0}, baseTemp)->AddFrame(Vec2{2, 0}, baseTemp)->AddFrame(Vec2{3, 0}, baseTemp)
                        ->AddFrame(Vec2{0, 0}, baseTemp)->AddFrame(Vec2{1, 0}, baseTemp)->AddFrame(Vec2{2, 0}, baseTemp)->AddFrame(Vec2{3, 0}, baseTemp)
                        ->AddFrame(Vec2{4, 0}, baseTemp);
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
                                  new CoroTaskCall([this, appState, newAngle, canChangeAnim](auto&& yield) {
                                  walk(std::forward<decltype(yield)>(yield), this, appState, newAngle, canChangeAnim); }));
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

    rx::observable<PlayerMoveData *> Player::OnMoveBegin() const
    {
        return m_OnMoveBegin.get_observable();
    }

    rx::observable<PlayerMoveData*> Player::OnMoveFinish() const
    {
        return m_OnMoveFinish.get_observable();
    }

    void Player::scrollByTracking(const Vec2<double> &trackingPos)
    {
        if (isRunningFieldEvent()) return;

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

    bool Player::isRunningFieldEvent()
    { return m_ParentalScene->GetFieldEventManager()->IsRunning(); }


    void Player::Init()
    {
        const double fps60 = 1.0 / 60;

        m_SubProcess.Birth(new ProcessTimer([&]() {
            auto scrollPos = m_ParentalScene->GetScrollManager()->CalcScrollToCenter(GetPos());
            scrollPos = m_ParentalScene->GetScrollManager()->MakePosInFieldRange(scrollPos);
//            constexpr int overhangByWalk = 60;
//            if (m_State.GetState()==EPlayerState::Walk)
//                scrollPos = scrollPos - Angle(m_Angle).ToXY().CastTo<double>() * overhangByWalk;
            scrollByTracking(scrollPos);
            return EProcessStatus::Running;
        }, fps60));

    }

    rx::observable<PlayerActionData *> Player::OnAction() const
    {
        return m_OnAction.get_observable();
    }


}
