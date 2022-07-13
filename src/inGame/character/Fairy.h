//
// Created by sashi0034 on 2022/07/13.
//

#ifndef FILL_TILES_FAIRY_H
#define FILL_TILES_FAIRY_H


#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{
    class Fairy : public CharacterBase
    {
    public:
        Fairy(IMainScene *mainScene, const MatPos &matPos, const std::string &message);
    private:
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{24, 24};
    };
}


#endif //FILL_TILES_FAIRY_H
