//
// Created by sashi0034 on 2022/06/24.
//

#include "MineFlowerManager.h"
#include "Player.h"
#include "character/MineFlower.h"

namespace inGame{

    MineFlowerClass::MineFlowerClass(const field::ETileKind mineFlowerTile, const field::ETileKind blockTile)
            : MineFlowerTile(mineFlowerTile), BlockTile(blockTile)
    {}

    void MineFlowerClass::IncreaseMineFlower()
    {
        ++m_MineFlowerCount;
    }

    void MineFlowerClass::DecreaseMineFlower()
    {
        --m_MineFlowerCount;
        std::cout << m_MineFlowerCount<<"%%\n";
    }

    bool MineFlowerClass::HasMineFlower()
    {
        return m_MineFlowerCount>0;
    }

    MineFlowerManager::MineFlowerManager(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene)
        : ActorBase(belonging), m_MainScene(mainScene)
    {
        using kind = field::ETileKind;
        m_MineFlowerClass.emplace_back(kind::mine_flower_1, kind::checkpoint_block_1);
        m_MineFlowerClass.emplace_back(kind::mine_flower_2, kind::checkpoint_block_2);
        m_MineFlowerClass.emplace_back(kind::mine_flower_3, kind::checkpoint_block_3);
        m_MineFlowerClass.emplace_back(kind::mine_flower_4, kind::checkpoint_block_4);
    }

    void MineFlowerManager::Init()
    {
        for (auto& mineClass: m_MineFlowerClass)
            initMineFlowerCount(mineClass);

        m_MainScene->GetPlayer()->OnMoveFinish().subscribe([&](MatPos matPos) {
            const auto field = m_MainScene->GetFieldManager();
            if (field->GetTileMap()->GetElementAt(matPos.GetVec())->IsBloomedMineFlower()) return;

            if (!field->GetTileMap()->IsInRange(matPos.GetVec())) return;

            for (auto& mineClass: m_MineFlowerClass)
                checkBloomMineFlower(matPos, mineClass);
        });


    }

    void MineFlowerManager::checkBloomMineFlower(const MatPos &matPos, MineFlowerClass &mineClass)
    {
        const auto field = m_MainScene->GetFieldManager();

        if (field->GetTileMap()->HasChipAt(matPos.GetVec(), mineClass.MineFlowerTile)!=Boolean::True) return;

        field->GetCharacterPool()->Birth(new character::MineFlower(m_MainScene, matPos));

        auto writable = field->GetTileMap()->GetElementWritableAt(matPos.GetVec());

        writable->SetIsBloomedMineFlower(true);

        mineClass.DecreaseMineFlower();

        if (!mineClass.HasMineFlower())
            std::cout << "all eliminated" << std::endl;
    }

    void MineFlowerManager::initMineFlowerCount(MineFlowerClass &mineClass)
    {
        const auto field = m_MainScene->GetFieldManager();
        const auto matSize = field->GetTileMap()->GetMatSize();

        for (int x = 0; x < matSize.X; ++x)
            for (int y = 0; y < matSize.Y; ++y)
                if (field->GetTileMap()->HasChipAt(Vec2{x, y}, mineClass.MineFlowerTile) == Boolean::True)
                    mineClass.IncreaseMineFlower();
    }

}

