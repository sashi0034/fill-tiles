//
// Created by sashi0034 on 2022/07/01.
//

#include "CheckpointBlock.h"
#include "../ZIndex.h"

namespace inGame::character
{

    CheckpointBlock::CheckpointBlock(IMainScene *mainScene, const MatPos &matPos, field::ETileKind tileKind)
            : CharacterBase(mainScene->GetFieldManager()),
            m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->ResImage->folder_16x16.get()),
            m_MatPos(matPos)
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(FieldManager::CharacterPadding);

        auto field =mainScene->GetFieldManager();
        field->OverwriteWallFlag(matPos, true);
        field->GetCheckpointBlockList()[tileKind].push_back(this);

        mainScene->GetFieldManager()->OnUpdatedChip().subscribe([this, field, matPos, tileKind](auto){
            if (field->GetTileMap()->HasChipAt(matPos.GetVec(), tileKind)!=Boolean::True)
            {
                this->getBelongingPool()->Destroy(this);
            }
        });

        ZIndexCharacter(m_View).ApplyZ();

        constexpr double duration = 0.1;
        field->GetAnimator()->TargetTo(m_View.GetView().GetWeakPtr())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, duration * 4)
                ->AddFrame(Vec2{1, 0}, duration)
                ->AddFrame(Vec2{2, 0}, duration)
                ->AddFrame(Vec2{3, 0}, duration);
    }

    MatPos CheckpointBlock::GetMatPos() const
    {
        return m_MatPos;
    }
}