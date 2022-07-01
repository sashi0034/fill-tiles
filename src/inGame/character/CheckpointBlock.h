//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_CHECKPOINTBLOCK_H
#define FILL_TILES_CHECKPOINTBLOCK_H

#include "../MainScene.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{
    class CheckpointBlock : public CharacterBase
    {
        DEF_WEAK_GET(CheckpointBlock);
    public:
        CheckpointBlock(IMainScene *mainScene, const MatPos &matPos, field::ETileKind tileKind);
        CharacterViewModel m_View;
        MatPos GetMatPos() const;

        void Destroy() override;
    private:
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        MatPos m_MatPos;
    };
}


#endif //FILL_TILES_CHECKPOINTBLOCK_H
