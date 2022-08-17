//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_PLAYER_H
#define FILL_TILES_PLAYER_H

#include "ActorBase.h"
#include "player/PlayerState.h"
#include "Angle.h"
#include "FieldManager.h"
#include "MainScene.h"
#include "CharacterViewModel.h"
#include "rx.h"
#include "player/PlayerMoveData.h"
#include "player/PlayerActionData.h"
#include "character/Catfish.h"
#include "player/PlayerAnimation.h"
#include "player/PlayerScroll.h"

using namespace inGame::player;

namespace inGame
{

    struct PlayerWalkArgs
    {
        IAppState *AppStateRef;
        EAngle NewAngle;
        bool CanChangeAnim;
        bool IsDash;
        bool IsFromOnIce;
    };

    class Player final : public ActorBase
    {
    public:
        explicit Player(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene);
        void Init() override;
        void Update(IAppState *appState) override;
        Vec2<double> GetPos();
        void SetPos(const Vec2<double> &pos);
        MatPos GetMatPos();
        [[nodiscard]] rx::observable<PlayerMoveData*> OnMoveBegin() const;
        [[nodiscard]] rx::observable<PlayerMoveData*> OnMoveFinish() const;
        [[nodiscard]] rx::observable<PlayerActionData*> OnAction() const;
        void ChangeStateToDead();
        PlayerScroll* GetScroll();

        static EAngle GetInputAngle(const Uint8 *keyState);
        static bool IsPushingConfirm(const Uint8 *keyState);

        static inline const Vec2<int> CellSize{32, 32};
    private:
        void setPos(Vec2<double> newPos);
        void initViewModel();

        void initAction();

        static bool isDashing(const Uint8 *keyState);

        unique_ptr<CharacterViewModel> m_View{};
        unique_ptr<PlayerAnimation> m_AnimationLogic{};
        unique_ptr<PlayerScroll> m_PlayerScroll{};

        Graph* m_Image;

        TextureAnimator m_PlayerAnimator{};
        PlayerState m_State = PlayerState(EPlayerState::Walking);
        EAngle m_Angle = EAngle::Down;
        IMainScene* m_ParentalScene;
        IFieldManager* m_Field;

        ChildrenPool<ProcessTimer> m_SubProcess{};
        rx::subject<PlayerMoveData*> m_OnMoveBegin{};
        rx::subject<PlayerMoveData*> m_OnMoveFinish{};
        rx::subject<PlayerActionData*> m_OnAction;

        void changeStateToWalking(const PlayerWalkArgs& args);

        CoroTask wait(CoroTaskYield &yield, IAppState *appState);
        CoroTask walk(CoroTaskYield &yield, PlayerWalkArgs args);
        CoroTask performDead(CoroTaskYield& yield, IAppState* appState);

        EAngle tryWalkOrActionByInput(CoroTaskYield &yield, const IAppState *appState);

        bool isRunningFieldEvent();

        void waitFieldEvent(CoroTaskYield &yield);

        void tackleToFieldObject(CoroTaskYield &yield, EAngle angle, const std::function<void()> &onTackleHit);

        void pushCatfish(CoroTaskYield &yield, EAngle &inputAngle, inGame::character::Catfish *catfish);

        bool checkPushMovableObject(CoroTaskYield &yield, EAngle &inputAngle, character::MovableObjectLogic* movable);
    };


}


#endif //FILL_TILES_PLAYER_H
