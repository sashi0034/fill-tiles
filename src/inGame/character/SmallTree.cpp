//
// Created by sashi0034 on 2022/06/17.
//

#include "SmallTree.h"
#include "../ZIndex.h"

namespace inGame::character{

    SmallTree::SmallTree(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->ResImage->tree_16x16.get())
    {
        m_View.GetView()->SetSrcRect(Rect{0, 0, 16, 16});;

        m_View.SetModelPos(matPos);

        m_View.GetView()->SetSrcRect(Rect{0, 0, 16, 16});

        m_View.GetView()->SetPosition(FieldManager::CharacterPadding);

        mainScene->GetFieldManager()->GetCharacterAnimator()->TargetTo(m_View.GetViewShared())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(Vec2{16, 16})->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, 0.2)
                ->AddFrame(Vec2{1, 0}, 0.2)
                ->AddFrame(Vec2{2, 0}, 0.2)
                ->AddFrame(Vec2{3, 0}, 0.4);

        ZIndexCharacter(m_View).ApplyZ();
    }
}
