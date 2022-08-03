//
// Created by sashi0034 on 2022/08/03.
//

#include "EffectTest.h"
#include "../MainScene.h"
#include "../effect/BombExplosion.h"
#include "../Player.h"

namespace inGame::test
{
    EffectTest::EffectTest(IMainScene *sceneRef, IChildrenPool<ActorBase> *children)
    : ActorBase(children),
    m_SceneRef(sceneRef),
    m_FileChangeDetector("assets/lua")
    {}

    void EffectTest::Update(IAppState *appState)
    {
        const auto lua = m_SceneRef->GetRoot()->GetLua();

        if (m_FileChangeDetector.CheckChanged())
        {
            lua->ReloadAllFiles();

            const std::string testStr = lua->GetState()["Test"]();
            std::cout << testStr << std::endl;

            effect::BombExplosion::Produce(
                    m_SceneRef->GetEffectManager(),
                    m_SceneRef->GetPlayer()->GetPos() + FieldManager::MatPixelSize.CastTo<double>()/2.0);

        }

        (void)appState;
    }
} // inGame