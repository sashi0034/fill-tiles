//
// Created by sashi0034 on 2022/07/18.
//

#ifndef FILL_TILES_PUNICAT_H
#define FILL_TILES_PUNICAT_H

#include "CharacterBase.h"
#include "../MainScene.h"
#include "../MatPos.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{

    class PuniCat final: public CharacterBase, public ISprRectColliderOwner
    {
    public:
        PuniCat(IMainScene *mainScene, const MatPos &matPos);

        void Update(IAppState *app) override;

    private:
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{24, 24};
    };

} // inGame

#endif //FILL_TILES_PUNICAT_H
