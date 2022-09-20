//
// Created by sashi0034 on 2022/09/20.
//

#ifndef FILL_TILES_STAGECLEAREVENT_H
#define FILL_TILES_STAGECLEAREVENT_H

#include "MainScene.h"

namespace inGame
{
    struct StageClearEventArgs
    {
        IMainScene* const SceneRef;

        [[nodiscard]] GameRoot* GetRoot() const;
        [[nodiscard]] TextureAnimator* GetAnimator() const;
        [[nodiscard]] CoroutineManager* GetCoroutineManager() const;
    };

    class StageClearEvent
    {
    public:
        static void Start(const StageClearEventArgs& args);
    private:
        static void startEvent(CoroTaskYield &yield, StageClearEventArgs args);
    };

} // inGame

#endif //FILL_TILES_STAGECLEAREVENT_H
