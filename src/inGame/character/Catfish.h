//
// Created by sashi0034 on 2022/07/18.
//

#ifndef FILL_TILES_CATFISH_H
#define FILL_TILES_CATFISH_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{

    class Catfish final: public CharacterBase, public ISprRectColliderOwner
    {
    public:
        Catfish(IMainScene *mainScene, const MatPos &matPos);
        bool TryMove(EAngle angle);

        void Update(IAppState *app) override;

    private:
        IMainScene* m_Scene;
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{24, 24};
        void move(CoroTaskYield& yield, EAngle angle);
    };

} // inGame

#endif //FILL_TILES_CATFISH_H
