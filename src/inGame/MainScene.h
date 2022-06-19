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
#include "ScrollManager.h"

namespace inGame
{
    class GameRoot;

    class IMainScene
    {
    public:
        virtual GameRoot* GetRoot() = 0;
        virtual ScrollManager* GetScrollManager() = 0;
        virtual IFieldManager* GetFieldManager() = 0;
    };

    class MainScene: public ActorBase, public IMainScene
    {
    public:
        explicit MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root);
        ~MainScene();
        TextureAnimator& GetTextureAnimator();
        void Update(IAppState* appState) override;
        GameRoot *GetRoot() override;
        IFieldManager* GetFieldManager() override;
        ScrollManager *GetScrollManager() override;
    private:
        void init();

        GameRoot* m_Root;
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        FieldManager* m_FieldManager{};
        unique_ptr<ScrollManager> m_ScrollManager{};
    };
}


#endif //FILL_TILES_MAINSCENE_H
