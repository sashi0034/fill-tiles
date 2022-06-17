//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_TREE_H
#define FILL_TILES_TREE_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "ViewModelTexture.h"

namespace inGame::character
{
    class Tree : public CharacterBase
    {
    public:
        Tree(IMainScene *mainScene, const MatPos &matPos);

        ViewModelTexture m_View;
    };
}


#endif //FILL_TILES_TREE_H
