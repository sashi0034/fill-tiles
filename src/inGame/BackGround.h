//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_BACKGROUND_H
#define FILL_TILES_BACKGROUND_H

#include "ActorBase.h"

namespace inGame
{
    class BackGround : public ActorBase
    {
    public:
        explicit BackGround(IChildrenPool<ActorBase>* belongingPool);
    private:
        shared_ptr<SpriteTexture> m_Spr;
        void render(IAppState* appState);
    };
}


#endif //FILL_TILES_BACKGROUND_H
