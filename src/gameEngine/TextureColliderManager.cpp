//
// Created by sashi0034 on 2022/06/18.
//

#include "TextureColliderManager.h"
#include "Range.h"
#include "arrayUtil.h"

namespace gameEngine
{


    TextureColliderManager::TextureColliderManager()
    = default;

    void TextureColliderManager::AddCollider(const WeakPtr<TextureCollider> &collider)
    {
        m_ColliderList.push_back(collider);
    }

    bool TextureColliderManager::IsHitWith(const Rect<double> &checkingRect)
    {
        return isHitWith<Rect<double>>(checkingRect);
    }

    bool TextureColliderManager::IsHitWith(const Vec2<double> &checkingPoint)
    {
        return isHitWith<Vec2<double>>(checkingPoint);
    }

    template<typename T>
    bool TextureColliderManager::isHitWith(const T &checkingOther)
    {
        int size = m_ColliderList.size();
        std::vector<int> garbageIndexes{};
        bool result = false;

        for (int i = 0; i < size; ++i)
            if (auto collider = m_ColliderList[i].GetPtr())
            {
                if (collider->IsIntersectWith(checkingOther)) result = true;
            }
            else
                garbageIndexes.push_back(i);

        collectGarbage(garbageIndexes);

        return result;
    }

    void TextureColliderManager::collectGarbage(const std::vector<int> &upwardIndexes)
    {
        for (int i= upwardIndexes.size() - 1; i >= 0; --i)
        {
            int index = upwardIndexes[i];
            m_ColliderList.erase(m_ColliderList.begin() + index);
        }
    }



}