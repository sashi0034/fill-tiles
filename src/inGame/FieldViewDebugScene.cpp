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

        scrollByMouse(appState);
    }

    void FieldViewDebugScene::scrollByMouse(const IAppState *appState)
    {
        auto mouse = appState->GetMouseState();
        if (mouse->GetPushed(EMouseButton::Left))
        {
            const auto mousePos = mouse->GetPosition();

            if (!m_IsClickedBefore)
            {
                m_PosOnClicked = mousePos;
                m_IsClickedBefore = true;
            }

            const auto diff = mousePos - m_PosOnClicked;
            const double vel = -0.1;
            auto newPos = m_ScrollManager->GetScroll() + diff * vel;

            auto matSize = m_FieldManager->GetTileMap()->GetMatSize();
            const double margin = 32;

            const double maxX = margin;
            const double maxY = margin;

            const double minX = -matSize.X * FieldManager::PixelPerMat+appState->GetScreenSize().X-margin;
            const double minY = -matSize.Y * FieldManager::PixelPerMat+appState->GetScreenSize().Y-margin;

            newPos.X = Range<double>(minX, maxX).MakeInRange(newPos.X);
            newPos.Y = Range<double>(minY, maxY).MakeInRange(newPos.Y);

            m_ScrollManager->SetScroll(newPos);
        }
        else
        {
            m_IsClickedBefore = false;
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
