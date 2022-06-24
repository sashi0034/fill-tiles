//
// Created by sashi0034 on 2022/06/24.
//

#ifndef FILL_TILES_MINEFLOWERMANAGER_H
#define FILL_TILES_MINEFLOWERMANAGER_H


#include "ActorBase.h"
#include "MainScene.h"

namespace inGame
{
    class MineFlowerManager final : public ActorBase
    {
    public:
        MineFlowerManager(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene);
        void Init() override;
    private:
        IMainScene* m_MainScene;

    };
}


#endif //FILL_TILES_MINEFLOWERMANAGER_H
