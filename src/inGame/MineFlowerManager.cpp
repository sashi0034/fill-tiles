//
// Created by sashi0034 on 2022/06/24.
//

#include "MainScene.h"
#include "MineFlowerManager.h"
#include "Player.h"
#include "character/MineFlower.h"
#include "character/CheckpointBlock.h"
#include "PlayerMoveData.h"

namespace inGame{

    MineFlowerClass::MineFlowerClass(field::ETileKind mineFlowerTile, field::ETileKind blockTile, int classLevel)
            : MineFlowerTile(mineFlowerTile), BlockTile(blockTile), m_ClassLevel{classLevel}
    {}

    void MineFlowerClass::IncreaseMineFlower()
    {
        ++m_MineFlowerCount;
    }

    void MineFlowerClass::DecreaseMineFlower()
    {
        --m_MineFlowerCount;
    }

    bool MineFlowerClass::HasMineFlower()
    {
        return m_MineFlowerCount>0;
    }

    int MineFlowerClass::GetClassLevel() const
    {
        return m_ClassLevel;
    }

    int MineFlowerClass::GetMaxMineFlowerCount() const
    {
        return m_MaxMineFlowerCount;
    }

    void MineFlowerClass::FixMaxMineFlowerCount()
    {
        assert(m_MaxMineFlowerCount==0);
        m_MaxMineFlowerCount = m_MineFlowerCount;
    }

    int MineFlowerClass::GetMineFlowerCount() const
    {
        return m_MineFlowerCount;
    }

    MineFlowerManager::MineFlowerManager(IMainScene *mainScene)
        : m_MainScene(mainScene)
    {
        using kind = field::ETileKind;
        m_MineFlowerClass.emplace_back(kind::mine_flower_1, kind::checkpoint_block_1, 1);
        m_MineFlowerClass.emplace_back(kind::mine_flower_2, kind::checkpoint_block_2, 2);
        m_MineFlowerClass.emplace_back(kind::mine_flower_3, kind::checkpoint_block_3, 3);
        m_MineFlowerClass.emplace_back(kind::mine_flower_4, kind::checkpoint_block_4, 4);

        m_CurrMineFlowerClass = &m_MineFlowerClass[0];
    }

    void MineFlowerManager::Init()
    {
        for (auto& mineClass: m_MineFlowerClass)
            initMineFlowerCount(mineClass);

        m_MainScene->GetPlayer()->OnMoveFinish().subscribe([&](PlayerMoveData* moveData) {
            const auto playerPos = moveData->AfterPos;
            const auto field = m_MainScene->GetFieldManager();

            if (!field->GetTileMap()->IsInRange(playerPos.GetVec())) return;

            CheckStepOnMine(playerPos);
        });


    }

    void MineFlowerManager::CheckStepOnMine(const MatPos &pos)
    {
        for (auto & mineClass : m_MineFlowerClass)
        {
            bool isExist = checkBloomMineFlower(pos, mineClass);
            if (!isExist) return;
        }
    }

    bool MineFlowerManager::checkBloomMineFlower(const MatPos &matPos, MineFlowerClass &mineClass)
    {
        const auto field = m_MainScene->GetFieldManager();

        if (field->GetTileMap()->HasChipAt(matPos.GetVec(), mineClass.MineFlowerTile)!=Boolean::True) return false;

        if (field->GetTileMap()->GetElementAt(matPos.GetVec())->IsBloomedMineFlower())
        {
            LOG_INFO << "stepped on mine." << std::endl;
            return false;
        }

        field->GetCharacterPool()->Birth(new character::MineFlower(m_MainScene, matPos));

        auto writable = field->GetTileMap()->GetElementWritableAt(matPos.GetVec());

        writable->SetIsBloomedMineFlower(true);

        mineClass.DecreaseMineFlower();

        m_CurrMineFlowerClass = &mineClass;

        if (!mineClass.HasMineFlower())
        {
            // 全消し演出
            field->GetCoroutine()->Start(new CoroTaskCall(std::bind(driveClearingCheckpointBlocksEvent,
                                                                    std::placeholders::_1, this, mineClass)));
        }
        return true;
    }

    void MineFlowerManager::initMineFlowerCount(MineFlowerClass &mineClass)
    {
        const auto field = m_MainScene->GetFieldManager();
        const auto matSize = field->GetTileMap()->GetMatSize();

        for (int x = 0; x < matSize.X; ++x)
            for (int y = 0; y < matSize.Y; ++y)
                if (field->GetTileMap()->HasChipAt(Vec2{x, y}, mineClass.MineFlowerTile) == Boolean::True)
                    mineClass.IncreaseMineFlower();

        mineClass.FixMaxMineFlowerCount();
    }

    CoroTask MineFlowerManager::driveClearingCheckpointBlocksEvent
        (CoroTaskYield &yield, MineFlowerManager *self, MineFlowerClass &mineClass)
    {
        const auto app = self->m_MainScene->GetRoot()->GetAppState();
        auto eventInScope = self->m_MainScene->GetFieldEventManager()->UseEvent();
        eventInScope.StartFromHere();

        const auto field = self->m_MainScene->GetFieldManager();

        std::vector<Vec2<int>> blockPosList{};
        Vec2<double> blockPosSum{};

        auto& blockList = field->GetCheckpointBlockList(mineClass.BlockTile);
        blockList.ForEach([&](auto&& block){
            const auto pos = block->GetMatPos().GetVec();
            blockPosList.push_back(pos);
            blockPosSum = blockPosSum + pos.template CastTo<double>() * FieldManager::PixelPerMat;
        });

        const int numBlock = blockPosList.size();

        const Vec2<double> centerPos = blockPosSum / numBlock;
        const auto scrollPos = self->m_MainScene->GetScrollManager()->CalcScrollToCenter(centerPos);

        // チェックポイントのブロックがあるところまで画面をスクロール
        auto animation = field->GetAnimator()->TargetTo(*self->m_MainScene->GetScrollManager()->GetSprite())
                ->AnimPosition(scrollPos, 2.0)->ToWeakPtr();
        coroUtil::WaitForExpire(yield, animation);

        // スクロールが終わるまで待機
        coroUtil::WaitForExpire(yield, animation);

        // ちょっと待機
        coroUtil::WaitForTime(yield, app->GetTime(), 0.5);

        // ブロックを削除
        blockList.ForEach([&](character::CheckpointBlock* block){
            block->InvokeDestroyEffect();
            block->Destroy();
            coroUtil::WaitForTime(yield, app->GetTime(), 0.05);
        });

        // ちょっと待機
        coroUtil::WaitForTime(yield, app->GetTime(), 0.5);
    }

    MineFlowerClass *MineFlowerManager::GetCurrMineFlowerClass()
    {
        return m_CurrMineFlowerClass;
    }

    MineFlowerClass *MineFlowerManager::GetNextMineFlowerClass()
    {
        int currLevel = m_CurrMineFlowerClass->GetClassLevel();

        if (currLevel==int(m_MineFlowerClass.size())) return nullptr;

        auto&& next = m_MineFlowerClass.at(currLevel);
        LOG_ASSERT(next.GetClassLevel() == currLevel + 1, "m_MineFlowerClassがレベル順になっていない可能性があります。");
        return &next;
    }

    bool MineFlowerManager::IsMineFlowerMat(const MatPos &matPos) const
    {
        const auto field = m_MainScene->GetFieldManager();

        for (const auto & mineClass : m_MineFlowerClass)
            if (field->GetTileMap()->HasChipAt(matPos.GetVec(), mineClass.MineFlowerTile)==Boolean::True)
                return true;

        return false;
    }

}

