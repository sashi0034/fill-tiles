//
// Created by sashi0034 on 2022/06/17.
//

#include "Tree.h"
#include "../ZIndex.h"

namespace inGame::character{

    Tree::Tree(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->ResImage->tree_16x16.get())
    {
        m_View.GetView()->SetSrcRect(Rect{0, 0, 16, 16});;

        m_View.SetModelPos(matPos);

        m_View.GetView()->SetSrcRect(Rect{0, 0, 16, 16});

        m_View.GetView()->SetPosition(FieldManager::CharacterPadding);

        ZIndexCharacter(m_View).ApplyZ();
    }
}
