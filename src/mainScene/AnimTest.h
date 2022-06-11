//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_ANIMTEST_H
#define FILL_TILES_ANIMTEST_H

#include "../gameEngine/gameEngine.h"

using namespace boost::coroutines2;

namespace mainScene
{
    class AnimTest final : public ChildBase
    {
    public:
        explicit AnimTest(IChildrenPool<ChildBase> *belonging);
        void Update() override;
    private:
        Vec2<double> m_Pos{};
        shared_ptr<SpriteTexture> m_Texture;
        Graph *m_Image;
        coroutine<CoroTask>::pull_type m_Action;

        static CoroTask wait(coroutine<CoroTask>::push_type &yield, AnimTest *self);
    };
}


#endif //FILL_TILES_ANIMTEST_H
