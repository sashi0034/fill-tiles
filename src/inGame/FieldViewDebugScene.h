//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_FIELDVIEWDEBUGSCENE_H
#define FILL_TILES_FIELDVIEWDEBUGSCENE_H


#include "GameRoot.h"
#include "ScrollManager.h"
#include "MainScene.h"

namespace inGame
{

    class FieldViewDebugScene : public ActorBase, public IMainScene
    {
    public:
        FieldViewDebugScene(IChildrenPool<ActorBase> *parent, GameRoot *root);
        void Update(IAppState* appState) override;
        GameRoot *GetRoot() override;
        IFieldManager* GetFieldManager() override;
        ScrollManager *GetScrollManager() override;
    private:
        GameRoot* m_Root;
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        FieldManager* m_FieldManager{};
        unique_ptr<ScrollManager> m_ScrollManager{};
    };
}


#endif //FILL_TILES_FIELDVIEWDEBUGSCENE_H
