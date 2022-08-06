//
// Created by sashi0034 on 2022/06/24.
//

#ifndef FILL_TILES_MINEFLOWERMANAGER_H
#define FILL_TILES_MINEFLOWERMANAGER_H


#include "MineFlowerClass.h"

namespace inGame
{
    class MineFlowerManager
    {
    public:
        explicit MineFlowerManager(IMainScene *mainScene);
        void Init();
        MineFlowerClass* GetCurrMineFlowerClass();
        MineFlowerClass* GetNextMineFlowerClass();
        MineFlowerClass* GetMineFlowerClassByLevel(int level);

        bool IsMineFlowerMat(const MatPos& matPos) const;
        void CheckStepOnMine(const MatPos &pos);
    private:
        IMainScene* m_MainScene;
        std::vector<MineFlowerClass> m_MineFlowerClass{};
        MineFlowerClass* m_CurrMineFlowerClass{};

        void initMineFlowerCount(MineFlowerClass& mineClass);
        bool checkBloomMineFlower(const MatPos& matPos, MineFlowerClass& mineClass);

        static CoroTask driveClearingCheckpointBlocksEvent(CoroTaskYield &yield, MineFlowerManager *self, MineFlowerClass& mineClass);

    };
}


#endif //FILL_TILES_MINEFLOWERMANAGER_H
