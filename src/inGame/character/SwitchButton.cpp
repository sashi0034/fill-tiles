//
// Created by sashi0034 on 2022/08/15.
//

#include "SwitchButton.h"
#include "../ZIndex.h"

namespace inGame::character
{
    SwitchButton::SwitchButton(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
              mainScene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->button_floor_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        ZIndexBackGround(&m_View.GetView()).GoFront(1).ApplyZ();

//        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
//                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
//                ->AddFrame(Vec2{0, 0}, 0.2 * 10)
//                ->AddFrame(Vec2{1, 0}, 0.2)
//                ->AddFrame(Vec2{2, 0}, 0.2);
    }
} // inGame