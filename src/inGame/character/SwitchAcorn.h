//
// Created by sashi0034 on 2022/08/15.
//

#ifndef FILL_TILES_SWITCHACORN_H
#define FILL_TILES_SWITCHACORN_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{
    enum class ESwitchAcornKind
    {
        Red = 0,
        Blue,
    };

    class SwitchAcorn : public CharacterBase
    {
        DEF_WEAK_GET(SwitchAcorn);
    public:
        SwitchAcorn(IMainScene *mainScene, const MatPos &matPos, ESwitchAcornKind kind);
        const ESwitchAcornKind SwitchKind;
    private:
        IMainScene *mainScene;
        CharacterViewModel m_View;
        static const inline Vec2<int> cellMatSize = Vec2<int>{1, 1};
    };

} // inGame

#endif //FILL_TILES_SWITCHACORN_H
