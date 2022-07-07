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
#include "FieldEventManager.h"
#include "EffectManager.h"

namespace inGame
{
    class GameRoot;
    class Player;

    class IMainScene
    {
    public:
        virtual GameRoot* GetRoot() = 0;
        virtual ScrollManager* GetScrollManager() = 0;
        virtual IFieldManager* GetFieldManager() = 0;
        virtual Player* GetPlayer() = 0;
        virtual FieldEventManager* GetFieldEventManager() = 0;
        virtual EffectManager* GetEffectManager() = 0;
    };

    class MainScene: public ActorBase, public IMainScene
    {
    public:
        explicit MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root);
        ~MainScene();

        Player *GetPlayer() override;

        TextureAnimator& GetTextureAnimator();
        void Update(IAppState* appState) override;
        GameRoot *GetRoot() override;
        IFieldManager* GetFieldManager() override;
        ScrollManager *GetScrollManager() override;
        FieldEventManager *GetFieldEventManager() override;
        EffectManager* GetEffectManager() override;
    private:
        void init();

        GameRoot* m_Root;
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        FieldManager* m_FieldManager{};
        Player* m_Player;
        FieldEventManager m_FieldEventManager{};
        unique_ptr<ScrollManager> m_ScrollManager{};
        EffectManager* m_EffectManager;
    };
}


#endif //FILL_TILES_MAINSCENE_H
