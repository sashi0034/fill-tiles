//
// Created by sashi0034 on 2022/06/19.
//

#ifndef FILL_TILES_TEXTURECOLLIDER_H
#define FILL_TILES_TEXTURECOLLIDER_H

#include "SpriteTexture.h"
#include "ChildrenPool.h"

namespace gameEngine
{
    class TextureCollider
    {
    public:
        static shared_ptr<TextureCollider> Create(const Rect<int> &colliderRect, SpriteTexture *parentalLinkingPos);

        bool IsIntersectWith(const Rect<double> &checkingRect);

        bool IsIntersectWith(const Vec2<double> &checkingPoint);
    private:
        TextureCollider(const Rect<int> &colliderRect, SpriteTexture *parentalLinkingPos);
        Vec2<double> m_ColliderStartingPoint;
        Vec2<double> m_ColliderSize;
        SpriteTexture *m_LinkingPosSpr;
    };
}

#endif //FILL_TILES_TEXTURECOLLIDER_H
