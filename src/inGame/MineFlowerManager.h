//
// Created by sashi0034 on 2022/06/24.
//

#ifndef FILL_TILES_MINEFLOWERMANAGER_H
#define FILL_TILES_MINEFLOWERMANAGER_H


#include "ActorBase.h"
#include "MainScene.h"
#include "field/TileMapMatElement.h"

namespace inGame
{
    class MineFlowerClass
    {
    public:
        MineFlowerClass(field::ETileKind mineFlowerTile, field::ETileKind blockTile);

        const field::ETileKind MineFlowerTile;
        const field::ETileKind BlockTile;
        void IncreaseMineFlower();
        void DecreaseMineFlower();
        bool HasMineFlower();
    private:
        int m_MineFlowerCount = 0;
    };


    class MineFlowerManager final : public ActorBase
    {
    public:
        MineFlowerManager(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene);
        void Init() override;
    private:
        IMainScene* m_MainScene;
        std::vector<MineFlowerClass> m_MineFlowerClass{};
        void initMineFlowerCount(MineFlowerClass& mineClass);
        void checkBloomMineFlower(const MatPos& matPos, MineFlowerClass& mineClass);
    };
}


#endif //FILL_TILES_MINEFLOWERMANAGER_H
