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
        MineFlowerClass(field::ETileKind mineFlowerTile, field::ETileKind blockTile, int classLevel);

        const field::ETileKind MineFlowerTile;
        const field::ETileKind BlockTile;
        void IncreaseMineFlower();
        void DecreaseMineFlower();
        bool HasMineFlower();
        void FixMaxMineFlowerCount();

        int GetClassLevel() const;
        int GetMaxMineFlowerCount() const;
        int GetMineFlowerCount() const;
    private:
        int m_MaxMineFlowerCount = 0;
        int m_MineFlowerCount = 0;
        int m_ClassLevel{};
    };


    class MineFlowerManager final : public ActorBase
    {
    public:
        MineFlowerManager(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene);
        void Init() override;
        MineFlowerClass* GetCurrMineFlowerClass();
        MineFlowerClass* GetNextMineFlowerClass();
    private:
        IMainScene* m_MainScene;
        std::vector<MineFlowerClass> m_MineFlowerClass{};
        MineFlowerClass* m_CurrMineFlowerClass{};

        void initMineFlowerCount(MineFlowerClass& mineClass);
        bool checkBloomMineFlower(const MatPos& matPos, MineFlowerClass& mineClass);

        static CoroTask driveClearingCheckpointBlocksEvent(CoroTaskYield &yield, MineFlowerManager *self, MineFlowerClass& mineClass);

        void checkSteppedByPlayer(const MatPos &playerPos);
    };
}


#endif //FILL_TILES_MINEFLOWERMANAGER_H
