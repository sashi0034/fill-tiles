//
// Created by sashi0034 on 2022/06/12.
//

#ifndef FILL_TILES_MAINSCENE_H
#define FILL_TILES_MAINSCENE_H

#include "ActorBase.h"
#include "../gameEngine/ChildBase.h"
#include "resource/Image.h"
#include "TileMap.h"
#include "FieldManager.h"

namespace inGame
{
    class MainScene: public Singleton<MainScene>, public ActorBase
    {
    public:
        explicit MainScene(IAppState *appState, IChildrenPool<ActorBase> *parent);
        ~MainScene() override;
        const unique_ptr<resource::Image> ResImage;
        TextureAnimator& GetTextureAnimator();
        void Update(IAppState* appState) override;
    private:
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        unique_ptr<FieldManager> m_FieldManager{};
    };
}


#endif //FILL_TILES_MAINSCENE_H
