//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_PLAYER_H
#define FILL_TILES_PLAYER_H

#include "../gameEngine/gameEngine.h"
#include "PlayerState.h"

namespace mainScene
{
    class Player final : public ChildBase
    {
    public:
        explicit Player(IChildrenPool<ChildBase> *belonging);
        void Update() override;
    private:
        void initAction();

        Vec2<double> m_Pos{};
        shared_ptr<Sprite> m_Spr;
        shared_ptr<SpriteTexture> m_Texture;
        Graph* m_Image;

        PlayerState m_State = PlayerState(EPlayerState::Walk);

        static CoroTask wait(CoroTaskYield& yield, Player* self);
        static CoroTask walk(CoroTaskYield& yield, Player* self);
    };


}


#endif //FILL_TILES_PLAYER_H
