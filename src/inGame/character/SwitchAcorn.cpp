//
// Created by sashi0034 on 2022/08/15.
//

#include "SwitchAcorn.h"
#include "../ZIndex.h"

namespace inGame::character
{
    SwitchAcorn::SwitchAcorn(IMainScene *mainScene, const MatPos &matPos, ESwitchAcornKind kind)
            : CharacterBase(mainScene->GetFieldManager()),
              SwitchKind(kind),
              mainScene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->rb_acorn_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(FieldManager::CharacterPadding);

        mainScene->GetFieldManager()->OverwriteWallFlag(matPos, true);

        ZIndexCharacter(m_View).ApplyZ();

        int cellY = int(SwitchKind);
        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, cellY}, 0.2)
                ->AddFrame(Vec2{1, cellY}, 0.2)
                ->AddFrame(Vec2{2, cellY}, 0.2)
                ->AddFrame(Vec2{3, cellY}, 0.2);
    }

} // inGame