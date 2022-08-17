//
// Created by sashi0034 on 2022/08/17.
//

#ifndef FILL_TILES_GROWINGCHICK_H
#define FILL_TILES_GROWINGCHICK_H

#include "CharacterBase.h"
#include "../MainScene.h"
#include "../MatPos.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{
    enum class EGrowingChickGrowth
    {
        Egg,
        Child,
        Adult
    };

    class GrowingChick final : public CharacterBase, public ISprRectColliderOwner
    {
    public:
        GrowingChick(IMainScene *mainScene, const MatPos &matPos);

        void Update(IAppState *app) override;
    private:
        IMainScene* m_Scene;
        ITextureAnimator* animator = m_Scene->GetFieldManager()->GetAnimator();
        CharacterViewModel m_View;
        TextureAnimationWeakPtr m_AnimationRef{};
        EGrowingChickGrowth m_Growth = EGrowingChickGrowth::Egg;

        void subscribePlayerMove(IMainScene *mainScene, const Player *player);

        static const inline Vec2<int> cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int> eggCellSrcSize = Vec2<int>{16, 16};
        static const inline Vec2<int> childCellSrcSize = Vec2<int>{16, 16};
        static const inline Vec2<int> adultCellSrcSize = Vec2<int>{32, 32};

        void animWhenEgg();
        void startChildProcess(CoroTaskYield& yield);

        void setViewPos(const Vec2<int>& cellSize);
    };

} // inGame

#endif //FILL_TILES_GROWINGCHICK_H