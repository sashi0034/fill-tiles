//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_MAINROOT_H
#define FILL_TILES_MAINROOT_H

#include "../gameEngine/gameEngine.h"
#include "../gameEngine/ChildBase.h"

namespace mainScene
{
    class MainRoot
    {
    public:
        explicit MainRoot(IAppState* appState);
    private:
        shared_ptr<Sprite> m_Sprite{};
        ChildrenPool<ChildBase> m_Children{};
    };
}


#endif //FILL_TILES_MAINROOT_H
