//
// Created by sashi0034 on 2022/06/12.
//

#ifndef FILL_TILES_MAINSCENE_H
#define FILL_TILES_MAINSCENE_H

#include "ActorBase.h"
#include "../gameEngine/ChildBase.h"
#include "resource/Image.h"
#include "field/TileMap.h"
#include "FieldManager.h"
#include "FieldViewDebugScene.h"
#include "ScrollManager.h"

namespace inGame
{
    class GameRoot;

    class IMainScene : public IFieldViewDebugScene
    {
    public:
        virtual FieldManager & GetFieldManager() = 0;
    };

    class MainScene: public ActorBase, public IMainScene
    {
    public:
        explicit MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root);
        ~MainScene();
        TextureAnimator& GetTextureAnimator();
        GameRoot *GetRoot() override;
    public:
        void Update(IAppState* appState) override;
        FieldManager & GetFieldManager() override;
        ScrollManager *GetScrollManager() override;
    private:
        GameRoot* m_Root;
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        unique_ptr<FieldManager> m_FieldManager{};
        unique_ptr<ScrollManager> m_ScrollManager{};
    };
}


#endif //FILL_TILES_MAINSCENE_H
