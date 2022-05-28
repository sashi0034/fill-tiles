//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_BACKGROUND_H
#define FILL_TILES_BACKGROUND_H

#include "../gameEngine/gameEngine.h"

namespace mainScene
{
    class BackGround : public ChildBase
    {
    public:
        explicit BackGround(IChildrenPool<ChildBase>* belongingPool);
    private:
        shared_ptr<Sprite> m_Spr;
        void render(IAppState* appState);
    };
}


#endif //FILL_TILES_BACKGROUND_H
