//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_MAINROOT_H
#define FILL_TILES_MAINROOT_H

#include "../gameEngine/gameEngine.h"
#include "../gameEngine/ChildBase.h"
#include "resource/Image.h"
#include "TileMap.h"

namespace mainScene
{
    class MainRoot : public Singleton<MainRoot>
    {
    public:
        explicit MainRoot(IAppState* appState);
        ~MainRoot() override;
        const unique_ptr<resource::Image> ResImage;
        IAppState* GetAppState();
        TextureAnimator& GetTextureAnimator();
    private:
        shared_ptr<SpriteTexture> m_Spr{};
        ChildrenPool<ChildBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        IAppState* m_AppState;
        unique_ptr<TileMap> test{new TileMap()};
        void createSelfSpr();
    };
}


#endif //FILL_TILES_MAINROOT_H
