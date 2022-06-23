//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_GAMEROOT_H
#define FILL_TILES_GAMEROOT_H

#include "ActorBase.h"
#include "resource/Image.h"

namespace inGame
{
    class GameRoot : public Singleton<GameRoot>
    {
    public:
        explicit GameRoot(IAppState* appState);
        ~GameRoot() override;
        const unique_ptr<resource::Image> ResImage;
        IAppState* GetAppState();
        TextureAnimator& GetTextureAnimator();
    private:
        SpriteTexture m_Spr = SpriteTexture::Create();
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        IAppState* m_AppState;
        void createSelfSpr();
    };
}


#endif //FILL_TILES_GAMEROOT_H
