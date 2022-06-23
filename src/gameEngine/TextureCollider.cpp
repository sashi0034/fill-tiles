//
// Created by sashi0034 on 2022/06/19.
//


#include "TextureCollider.h"
#include "Range.h"


namespace gameEngine{
    TextureCollider::TextureCollider(const Rect<int> &colliderRect, SpriteTexture *parentalLinkingPos)
            : m_ColliderStartingPoint(colliderRect.GetStartingPoint().CopyBy<double>()),
              m_ColliderSize(colliderRect.GetSize().CopyBy<double>()),
              m_LinkingPosSpr(parentalLinkingPos)
    {}

    bool TextureCollider::IsIntersectWith(const Rect<double> &checkingRect)
    {
        const auto selfTexturePos = m_LinkingPosSpr->GetPosition();
        const auto selfColliderPos = selfTexturePos + m_ColliderStartingPoint;
        const auto selfRect = Rect<double>(selfColliderPos, m_ColliderSize);

        bool isIntersect = selfRect.IsIntersectWith(checkingRect);
        return isIntersect;
    }

    bool TextureCollider::IsIntersectWith(const Vec2<double> &checkingPoint)
    {
        const auto selfTexturePos = m_LinkingPosSpr->GetPosition();
        const auto selfColliderPos = selfTexturePos + m_ColliderStartingPoint;

        bool isIntersect = Range(selfColliderPos.X, selfColliderPos.X + m_ColliderSize.X).IsBetween(checkingPoint.X)
                           && Range(selfColliderPos.Y, selfColliderPos.Y + m_ColliderSize.Y).IsBetween(checkingPoint.Y);
        return isIntersect;
    }

    unique_ptr<TextureCollider>
    TextureCollider::Create(const Rect<int> &colliderRect, SpriteTexture *parentalLinkingPos)
    {
        auto product = unique_ptr<TextureCollider>(new TextureCollider(colliderRect, parentalLinkingPos));
        return product;
    }

}