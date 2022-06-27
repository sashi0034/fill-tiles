//
// Created by sashi0034 on 2022/06/16.
//

#include "ScrollManager.h"

namespace inGame
{
    ScrollManager::ScrollManager(IMainScene *parentScene)
            : m_ParentScene(parentScene)
    {}

    void ScrollManager::RegisterSprite(SpriteTexture &target)
    {
        target.SetPositionParent(m_ViewModel);
    }

    Vec2<double> ScrollManager::GetScroll()
    {
        return m_ViewModel.GetPosition();
    }

    void ScrollManager::SetScroll(const Vec2<double> &amount)
    {
        m_ViewModel.SetPosition(amount);
    }

    WeakPtr<SpriteTexture> ScrollManager::GetSprite()
    {
        return m_ViewModel.GetWeakPtr();
    }
}
