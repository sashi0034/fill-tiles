//
// Created by sashi0034 on 2022/08/19.
//

#ifndef FILL_TILES_WARPTILE_H
#define FILL_TILES_WARPTILE_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{

    class WarpTile : public CharacterBase
    {
    public:
        WarpTile(IMainScene *mainScene, const MatPos &matPos);
        CharacterViewModel m_View;
    private:
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
    };

} // inGame

#endif //FILL_TILES_WARPTILE_H
