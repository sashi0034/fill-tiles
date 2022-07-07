//
// Created by sashi0034 on 2022/06/16.
//

#include "FieldViewDebugScene.h"

#include <memory>
#include "field/TileMap.h"

namespace inGame{

    FieldViewDebugScene::FieldViewDebugScene(IChildrenPool<ActorBase> *parent, GameRoot *root, Vec2<double> startScrollPos)
            : ActorBase(parent), m_Root(root), m_FileDetector(field::TileMap::TileMapDirectory)
    {
        m_ScrollManager = std::make_unique<ScrollManager>(this);
        m_ScrollManager->SetScroll(startScrollPos);

        m_FieldManager = m_ChildrenPool.BirthAs<FieldManager>(new FieldManager(&m_ChildrenPool, this));

        m_ChildrenPool.ProcessEach([&](auto& child){ child.Init();});

        m_ProcessUntilFileChanged = std::make_unique<ProcessTimer>([&](){
            bool changed = m_FileDetector.CheckChanged();
            if (changed) return EProcessStatus::Dead;
            return EProcessStatus::Running;
        }, 0.5);
    }

    void FieldViewDebugScene::Update(IAppState *appState)
    {
        m_ChildrenPool.ProcessEach([&](auto& child){ child.Update(appState);});

        scrollByMouse(appState);

        m_ProcessUntilFileChanged->Update(appState->GetTime().GetDeltaSec());
        if (m_ProcessUntilFileChanged->GetStatus()==EProcessStatus::Dead)
        {
            auto pool = getBelongingPool();
            auto scroll = m_ScrollManager->GetScroll();
            pool->Destroy(this);
            pool->Birth(new FieldViewDebugScene(pool, m_Root, scroll));
        }
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

    FieldViewDebugScene::~FieldViewDebugScene()
    {
        m_ChildrenPool.Release();
    }

    Player *FieldViewDebugScene::GetPlayer()
    {
        return nullptr;
    }

    FieldEventManager *FieldViewDebugScene::GetFieldEventManager()
    {
        return nullptr;
    }

    EffectManager *FieldViewDebugScene::GetEffectManager()
    {
        return nullptr;
    }
}
