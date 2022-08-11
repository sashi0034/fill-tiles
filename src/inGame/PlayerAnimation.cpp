//
// Created by sashi0034 on 2022/08/11.
//

#include "PlayerAnimation.h"
#include "Player.h"
#include "ParabolaAnimation.h"

namespace inGame
{
    void PlayerAnimation::AnimWalk(EAngle angle, double frameSpeed)
    {
        animator.Release();
        const double baseTemp = 0.2 * frameSpeed;

        switch (angle)
        {
            case EAngle::Up:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 5}, baseTemp)->AddFrame(Vec2{1, 5}, baseTemp)->AddFrame(Vec2{2, 5}, baseTemp)->AddFrame(Vec2{3, 5}, baseTemp);
                break;
            case EAngle::Right:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 4}, baseTemp)->AddFrame(Vec2{1, 4}, baseTemp)->AddFrame(Vec2{2, 4}, baseTemp)
                        ->AddFrame(Vec2{3, 4}, baseTemp)->AddFrame(Vec2{4, 4}, baseTemp)->AddFrame(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Left:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 4}, baseTemp)->AddFrameFlipped(Vec2{1, 4}, baseTemp)->AddFrameFlipped(Vec2{2, 4}, baseTemp)
                        ->AddFrameFlipped(Vec2{3, 4}, baseTemp)->AddFrameFlipped(Vec2{4, 4}, baseTemp)->AddFrameFlipped(Vec2{5, 4}, baseTemp);
                break;
            case EAngle::Down:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 3}, baseTemp)->AddFrame(Vec2{1, 3}, baseTemp)->AddFrame(Vec2{2, 3}, baseTemp)->AddFrame(Vec2{3, 3}, baseTemp);
                break;
            default:
                assert(false);
        }
    }

    void PlayerAnimation::AnimWait(EAngle angle)
    {
        animator.Release();
        const double baseTemp = 0.25;

        switch (angle)
        {
            case EAngle::Up:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 2}, baseTemp)->AddFrame(Vec2{1, 2}, baseTemp)->AddFrame(Vec2{2, 2}, baseTemp)->AddFrame(Vec2{3, 2}, baseTemp);
                break;
            case EAngle::Right:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 1}, baseTemp)->AddFrame(Vec2{1, 1}, baseTemp)->AddFrame(Vec2{2, 1}, baseTemp)
                        ->AddFrame(Vec2{0, 1}, baseTemp)->AddFrame(Vec2{1, 1}, baseTemp)->AddFrame(Vec2{2, 1}, baseTemp)
                        ->AddFrame(Vec2{3, 1}, baseTemp);
                break;
            case EAngle::Left:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrameFlipped(Vec2{0, 1}, baseTemp)->AddFrameFlipped(Vec2{1, 1}, baseTemp)->AddFrameFlipped(Vec2{2, 1}, baseTemp)
                        ->AddFrameFlipped(Vec2{0, 1}, baseTemp)->AddFrameFlipped(Vec2{1, 1}, baseTemp)->AddFrameFlipped(Vec2{2, 1}, baseTemp)
                        ->AddFrameFlipped(Vec2{3, 1}, baseTemp);
                break;
            case EAngle::Down:
                animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(true)
                        ->AddFrame(Vec2{0, 0}, baseTemp)->AddFrame(Vec2{1, 0}, baseTemp)->AddFrame(Vec2{2, 0}, baseTemp)->AddFrame(Vec2{3, 0}, baseTemp)
                        ->AddFrame(Vec2{0, 0}, baseTemp)->AddFrame(Vec2{1, 0}, baseTemp)->AddFrame(Vec2{2, 0}, baseTemp)->AddFrame(Vec2{3, 0}, baseTemp)
                        ->AddFrame(Vec2{4, 0}, baseTemp);
                break;
            default:
                assert(false);
        }
    }


    void PlayerAnimation::PerformDead(CoroTaskYield& yield, IAppState* appState)
    {
        animator.Release();
        yield();

        constexpr double baseTemp = 0.5;

        animator.TargetTo(view->GetView())->AnimGraph(cellSize)->SetFrameLoopEndless(false)
                ->AddFrame(Vec2{0, 6}, baseTemp * 2)->AddFrame(Vec2{1, 6}, baseTemp);

        constexpr double jumpingHeight = 24;
        ParabolaAnimation::Create(mainScene->GetEffectManager(), &view->GetView())
            ->SetSpeedByPeekHeightAndTime(jumpingHeight, baseTemp)
            ->AwaitForReturnToStart(yield)
            ->Forget();

        while(true)
        {
            yield();
        }

        (void)appState;
    }

    PlayerAnimation::PlayerAnimation(IMainScene *mainScene, const Vec2<int> &cellSize, TextureAnimator &animator,
                                     CharacterViewModel *const view) : mainScene(mainScene), cellSize(cellSize),
                                                                       animator(animator), view(view)
    {}
} // inGame