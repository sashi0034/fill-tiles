//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_PLAYER_H
#define FILL_TILES_PLAYER_H

#include "ActorBase.h"
#include "PlayerState.h"
#include "Angle.h"
#include "FieldManager.h"
#include "MainScene.h"
#include "CharacterViewModel.h"
#include "rxcpp/rx.hpp"

namespace rx
{
    using namespace rxcpp;
    using namespace rxcpp::subjects;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
}

namespace inGame
{
    class Player final : public ActorBase
    {
    public:
        explicit Player(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene);
        void Update(IAppState *appState) override;
        Vec2<double> GetPos();
        void SetPos(const Vec2<double> &pos);
        MatPos GetMatPos();
        [[nodiscard]] rx::observable<MatPos> OnMoveFinish() const;
        static inline const Vec2<int> CellSize{32, 32};
    private:
        void setPos(Vec2<double> newPos);
        void initViewModel();

        void initAction();

        static bool isDashing(const Uint8 *keyState);

        unique_ptr<CharacterViewModel> m_View{};
        Graph* m_Image;

        TextureAnimator m_PlayerAnimator{};
        PlayerState m_State = PlayerState(EPlayerState::Walk);
        EAngle m_Angle = EAngle::Down;
        IMainScene* m_ParentalScene;
        IFieldManager* m_Field;

        rx::subject<MatPos> m_OnMoveFinish;

        static EAngle getInputAngle(const Uint8 *keyState);
        void changeAnimation(const std::function<void()>& animation);
        void animWait(EAngle angle);
        void animWalk(EAngle angle, double frameSpeed);
        void changeStateToWalk(IAppState *appState, EAngle newAngle, bool canChangeAnim);

        static CoroTask wait(CoroTaskYield &yield, Player *self, IAppState *appState);
        static void walk(CoroTaskYield &yield, Player *self, IAppState *appState, EAngle goingAngle, bool canChangeAnim);

        static EAngle waitForWalkUntilInput(Player *self, const IAppState *appState);
    };


}


#endif //FILL_TILES_PLAYER_H
