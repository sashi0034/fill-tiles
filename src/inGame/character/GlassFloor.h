//
// Created by sashi0034 on 2022/08/12.
//

#ifndef FILL_TILES_GLASSFLOOR_H
#define FILL_TILES_GLASSFLOOR_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{

    class GlassFloor : public CharacterBase
    {
    public:
        GlassFloor(IMainScene *mainScene, const MatPos &matPos);
    private:
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{16, 16};
    };

} // inGame

#endif //FILL_TILES_GLASSFLOOR_H
