//
// Created by sashi0034 on 2022/06/24.
//

#include "MineFlowerManager.h"
#include "Player.h"
#include "character/SmallTree.h"

namespace inGame{

    MineFlowerManager::MineFlowerManager(IChildrenPool<ActorBase> *belonging, IMainScene *mainScene)
        : ActorBase(belonging), m_MainScene(mainScene)
    {}

    void MineFlowerManager::Init()
    {
        m_MainScene->GetPlayer()->OnMoveFinish().subscribe([&](MatPos matPos){
            const auto field = m_MainScene->GetFieldManager();
            if (field->GetTileMap()->HasChipAt(matPos.GetVec(), field::ETileKind::mine_flower)==Boolean::True)
                field->GetCharacterPool()->Birth(new character::SmallTree(m_MainScene, matPos));
        });
    }
}

