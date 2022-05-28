//
// Created by sashi0034 on 2022/05/23.
//

#include "ChildBase.h"

namespace gameEngine
{
    ChildBase::ChildBase(IChildrenPool<ChildBase>* belongingPool)
        : m_BelongingPool(belongingPool)
    {}

    IChildrenPool<ChildBase> *ChildBase::GetBelongingPool() const
    {
        return m_BelongingPool;
    }
}
