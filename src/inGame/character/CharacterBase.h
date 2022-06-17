//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_CHARACTERBASE_H
#define FILL_TILES_CHARACTERBASE_H

#include "../../gameEngine/gameEngine.h"
#include "../GameRoot.h"


namespace inGame{
    class IFieldManager;
}

namespace inGame::character
{
    class CharacterBase : ChildBase<CharacterBase>
    {
    public:
        explicit CharacterBase(IFieldManager *parentField);
    };
}


#endif //FILL_TILES_CHARACTERBASE_H
