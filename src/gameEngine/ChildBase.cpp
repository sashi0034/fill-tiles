//
// Created by sashi0034 on 2022/05/23.
//

#include "ChildBase.h"

namespace gameEngine
{
    ChildBase::ChildBase(ChildrenPool<ChildBase>* belongingPool)
        : m_BelongingPool(belongingPool)
    {}

    ChildrenPool<ChildBase> *ChildBase::GetBelongingPool() const
    {
        return m_BelongingPool;
    }
}
