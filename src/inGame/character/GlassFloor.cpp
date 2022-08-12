//
// Created by sashi0034 on 2022/08/12.
//

#include "GlassFloor.h"
#include "../ZIndex.h"

namespace inGame::character
{
    GlassFloor::GlassFloor(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->glass_floor_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        ZIndexCharacter(m_View).ApplyZ();

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, 0.2 * 10)
                ->AddFrame(Vec2{1, 0}, 0.2)
                ->AddFrame(Vec2{2, 0}, 0.2);
    }
} // inGame