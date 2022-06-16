//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_FIELDVIEWDEBUGSCENE_H
#define FILL_TILES_FIELDVIEWDEBUGSCENE_H


#include "GameRoot.h"
#include "ScrollManager.h"

namespace inGame
{
    class IFieldViewDebugScene
    {
    public:
        virtual GameRoot* GetRoot() = 0;
        virtual ScrollManager* GetScrollManager() = 0;
    };

    class FieldViewDebugScene : public IFieldViewDebugScene
    {

    };
}


#endif //FILL_TILES_FIELDVIEWDEBUGSCENE_H
