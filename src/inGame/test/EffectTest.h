//
// Created by sashi0034 on 2022/08/03.
//

#ifndef FILL_TILES_EFFECTTEST_H
#define FILL_TILES_EFFECTTEST_H

#include "../ActorBase.h"


namespace inGame
{
    class IMainScene;
}

namespace inGame::test
{

    class EffectTest : public ActorBase
    {
    public:
        explicit EffectTest(IMainScene *sceneRef, IChildrenPool<ActorBase> *children);

        void Update(IAppState *appState) override;

    private:
        IMainScene* m_SceneRef;
        DirChangeDetector m_FileChangeDetector;
    };

} // gameEngine

#endif //FILL_TILES_EFFECTTEST_H
