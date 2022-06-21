//
// Created by sashi0034 on 2022/06/18.
//

#ifndef FILL_TILES_TEXTURECOLLIDERMANAGER_H
#define FILL_TILES_TEXTURECOLLIDERMANAGER_H

#include "TextureCollider.h"

namespace gameEngine
{

    class TextureColliderManager
    {
    public:
        TextureColliderManager();
        void AddCollider(const WeakPtr<TextureCollider>& collider);
        bool IsHitWith(const Rect<double> &checkingRect);
        bool IsHitWith(const Vec2<double> &checkingPoint);
    private:
        std::vector<WeakPtr<TextureCollider>> m_ColliderList;
        void collectGarbage(const std::vector<int>& upwardIndexes);
        template <typename T> bool isHitWith(const T &checkingOther);
    };

}


#endif //FILL_TILES_TEXTURECOLLIDERMANAGER_H
