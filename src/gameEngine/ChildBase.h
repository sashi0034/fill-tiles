//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_CHILDBASE_H
#define FILL_TILES_CHILDBASE_H

#include "ChildrenPool.h"

namespace gameEngine
{
    class ChildBase
    {
    public:
        explicit ChildBase(IChildrenPool<ChildBase>* belongingPool);
        [[nodiscard]] IChildrenPool<ChildBase>* GetBelongingPool() const;
    private:
        IChildrenPool<ChildBase>* m_BelongingPool;
    };
}


#endif //FILL_TILES_CHILDBASE_H
