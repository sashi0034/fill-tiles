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

    class FieldViewDebugScene final: public ActorBase, public IMainScene
    {
    public:
        FieldViewDebugScene(IChildrenPool<ActorBase> *parent, GameRoot *root, Vec2<double> startScrollPos= Vec2<double>{0, 0});
        ~FieldViewDebugScene() override;
        void Update(IAppState* appState) override;
        GameRoot *GetRoot() override;
        IFieldManager* GetFieldManager() override;
        ScrollManager *GetScrollManager() override;

        Player *GetPlayer() override;
        FieldEventManager *GetFieldEventManager() override;

        EffectManager *GetEffectManager() override;

    private:
        GameRoot* m_Root;
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        FieldManager* m_FieldManager{};
        unique_ptr<ScrollManager> m_ScrollManager{};

        Vec2<double> m_PosOnClicked;
        bool m_IsClickedBefore = false;
        FileChangeDetector m_FileDetector;
        unique_ptr<ProcessTimer> m_ProcessUntilFileChanged{};

        void scrollByMouse(const IAppState *appState);
    };
}


#endif //FILL_TILES_FIELDVIEWDEBUGSCENE_H
