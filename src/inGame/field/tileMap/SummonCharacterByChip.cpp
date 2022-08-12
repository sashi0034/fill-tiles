//
// Created by sashi0034 on 2022/08/12.
//

#include "SummonCharacterByChip.h"
#include <boost/lexical_cast.hpp>
#include "ReadObjectInObjectGroup.h"
#include "../../Player.h"
#include "../../character/SmallTree.h"
#include "../../character/BigTree.h"
#include "../../character/CheckpointBlock.h"
#include "../../character/GlassFloor.h"


namespace inGame::field::tileMap
{
    bool SummonCharacterByChip(IMainScene* mainScene, const Vec2<int> &pos, ETileKind kind)
    {
        const auto matPos = MatPos(pos);
        const auto field = mainScene->GetFieldManager()->GetCharacterPool();

        switch (kind)
        {
            case ETileKind::small_tree:
                field->Birth(new character::SmallTree(mainScene, matPos));
                break;
            case ETileKind::big_tree:
                field->Birth(new character::BigTree(mainScene, matPos));
                break;
            case ETileKind::glass:
                field->Birth(new character::GlassFloor(mainScene, matPos));
                break;
            case ETileKind::checkpoint_block_1:
            case ETileKind::checkpoint_block_2:
            case ETileKind::checkpoint_block_3:
            case ETileKind::checkpoint_block_4:
                field->Birth(new character::CheckpointBlock(mainScene, matPos, kind));
                break;
            default:
                return false;
        }

        return true;
    }
} // inGame