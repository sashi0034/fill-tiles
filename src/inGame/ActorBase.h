//
// Created by sashi0034 on 2022/06/12.
//

#ifndef FILL_TILES_ACTORBASE_H
#define FILL_TILES_ACTORBASE_H

#include "../gameEngine/gameEngine.h"

namespace inGame
{
    class ActorBase : public ChildBase<ActorBase>
    {
    public:
        explicit ActorBase(IChildrenPool<ActorBase>* parentPool);
        virtual void Init();
        virtual void Update(IAppState* appState);
    };
}


#endif //FILL_TILES_ACTORBASE_H
