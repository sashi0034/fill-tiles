//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_SCROLLMANAGER_H
#define FILL_TILES_SCROLLMANAGER_H

#include "ActorBase.h"

namespace inGame
{
    class IMainScene;

    class ScrollManager final
    {
    public:
        explicit ScrollManager(IMainScene* parentScene);
        void RegisterSprite(shared_ptr<SpriteTexture>& target);

        Vec2<double> GetScroll();
        void SetScroll(const Vec2<double> &amount);
    private:
        shared_ptr<SpriteTexture> m_ViewModel;
        IMainScene* m_ParentScene;
    };
}


#endif //FILL_TILES_SCROLLMANAGER_H
