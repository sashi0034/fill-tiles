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
        Vec2<double> GetPos();
    private:
        void setPos(Vec2<double> newPos);
        void initViewModel();
        void initView();

        void initAction();

        shared_ptr<Sprite> m_ViewModelSprite;
        shared_ptr<SpriteTexture> m_ViewModelTexture;

        shared_ptr<Sprite> m_ViewSprite;
        shared_ptr<SpriteTexture> m_ViewTexture;
        Graph* m_Image;

        PlayerState m_State = PlayerState(EPlayerState::Walk);

        static CoroTask wait(CoroTaskYield& yield, Player* self);
        static CoroTask walk(CoroTaskYield& yield, Player* self);
    };


}


#endif //FILL_TILES_PLAYER_H
