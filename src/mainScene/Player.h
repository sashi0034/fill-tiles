//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_PLAYER_H
#define FILL_TILES_PLAYER_H

#include "../gameEngine/gameEngine.h"
#include "PlayerState.h"
#include "Angle.h"

namespace mainScene
{
    class Player final : public ChildBase
    {
    public:
        explicit Player(IChildrenPool<ChildBase> *belonging);
        void Update() override;
        Vec2<double> GetPos();
        static inline const Vec2<int> CellSize{32, 32};
    private:
        void setPos(Vec2<double> newPos);
        void initViewModel();
        void initView();

        void initAction();

        static bool isDashing(const Uint8 *keyState);

        shared_ptr<SpriteTexture> m_ViewModelTexture;

        shared_ptr<SpriteTexture> m_ViewTexture;
        Graph* m_Image;

        TextureAnimator m_PlayerAnimator{};
        PlayerState m_State = PlayerState(EPlayerState::Walk);
        EAngle m_Angle = EAngle::Down;

        static EAngle getInputAngle(const Uint8 *keyState);
        void animWait(EAngle angle);
        void animWalk(EAngle angle, double frameSpeed);
        void changeStateToWalk(IAppState *appState, EAngle newAngle, bool canChangeAnim);

        static CoroTask wait(CoroTaskYield &yield, Player *self, IAppState *appState);
        static void walk(CoroTaskYield &yield, Player *self, IAppState *appState, EAngle goingAngle, bool canChangeAnim);
    };


}


#endif //FILL_TILES_PLAYER_H
