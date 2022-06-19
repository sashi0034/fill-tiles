//
// Created by sashi0034 on 2022/06/16.
//

#include "FieldViewDebugScene.h"

namespace inGame{

    FieldViewDebugScene::FieldViewDebugScene(IChildrenPool<ActorBase> *parent, GameRoot *root)
            : ActorBase(parent), m_Root(root)
    {
        m_ScrollManager = std::make_unique<ScrollManager>(this);

        m_FieldManager = m_ChildrenPool.BirthAs<FieldManager>(new FieldManager(&m_ChildrenPool, this));

        m_ChildrenPool.ProcessEach([&](auto child){ child->Init();});
    }

    void FieldViewDebugScene::Update(IAppState *appState)
    {
        m_ChildrenPool.ProcessEach([&](auto child){ child->Update(appState);});

        auto pos = appState->GetMouseState()->GetPosition();
        std::cout << pos.X << "," << pos.Y << std::endl;

        if (appState->GetMouseState()->GetPushed(EMouseButton::Right))
        {
            std::cout << "R" << std::endl;
        }
        if (appState->GetMouseState()->GetPushed(EMouseButton::Left))
        {
            std::cout << "L" << std::endl;
        }
    }

    IFieldManager *FieldViewDebugScene::GetFieldManager()
    {
        return m_FieldManager;
    }

    GameRoot *FieldViewDebugScene::GetRoot()
    {
        return m_Root;
    }

    ScrollManager *FieldViewDebugScene::GetScrollManager()
    {
        return m_ScrollManager.get();
    }
}
