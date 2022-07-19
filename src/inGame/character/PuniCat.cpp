//
// Created by sashi0034 on 2022/07/18.
//

#include "PuniCat.h"
#include "../ZIndex.h"
#include "../Player.h"

namespace inGame::character
{
    PuniCat::PuniCat(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
            m_Scene(mainScene),
            m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->punicat_24x24.get())
    {
        const int pixelPerMat = FieldManager::PixelPerMat;
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellSrcSize});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSrcSize.X - pixelPerMat) / 2.0, double(cellSrcSize.Y - pixelPerMat)});

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 0}, 0.3)
                ->AddFrame(Vec2{1, 0}, 0.2)
                ->AddFrame(Vec2{2, 0}, 0.2)
                ->AddFrame(Vec2{3, 0}, 0.2);

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayerAction(mainScene, player);
        }
    }

    void PuniCat::subscribePlayerAction(IMainScene *mainScene, const Player *player)
    {
        player->OnAction().subscribe([&, mainScene](auto&& action){
           if (auto actionDetail = dynamic_cast<PlayerActionPushCatfish*>(action))
           {
               auto actedCatfish = actionDetail->TouchedCatfish;
               searchCatfishEveryAngle(mainScene, actedCatfish);
           }
        });
    }

    void PuniCat::searchCatfishEveryAngle(IMainScene *mainScene, Catfish *nullableTargetCatfish)
    {
        if (nullableTargetCatfish)
            if (!nullableTargetCatfish->GetEatableFlag().IsUpping()) return;

        const auto currPos = m_View.GetMatPos();

        for (auto angle : Angle::EveryAngle)
        {
            constexpr int maxStep = 8;
            // 各方向ごとに進めなくなるまでcatfishがあるかを確認していきます。
            for (int step=0; step<maxStep; ++step)
            {
                const auto stepVec = angle.ToXY();
                const MatPos checkingPos = currPos + MatPos(stepVec * step);
                const auto checking = mainScene->GetFieldManager()->CheckMoveTo(checkingPos, angle.GetKind());

                // どれを食べるか指定あり
                if (nullableTargetCatfish != nullptr)
                {
                    if (checking.CollidedObject == nullableTargetCatfish)
                        startGoToEatCatfish(mainScene, nullableTargetCatfish, stepVec, checkingPos);
                }
                // どれを食べるか指定なし
                else
                {
                    if (auto foundCatfish = dynamic_cast<Catfish*>(checking.CollidedObject))
                        startGoToEatCatfish(mainScene, foundCatfish, stepVec, checkingPos);
                }
                if (!checking.CanMove) break;
            }
        }
    }

    void PuniCat::startGoToEatCatfish(IMainScene *mainScene, Catfish *targetCatfish, const Vec2<int> &stepVec,
                                      const MatPos &checkingPos)
    {
        targetCatfish->GetEatableFlag().DownFlag();
        mainScene->GetFieldManager()->GetCoroutine()->Start(
                new CoroTaskCall([&](auto&& yield){ moveToEatFish(yield, checkingPos + MatPos(stepVec), targetCatfish);}));
    }

    void PuniCat::Update(IAppState *)
    {
        ZIndexCharacter(m_View).ApplyZ();
    }

    void PuniCat::moveToEatFish(CoroTaskYield &yield, const MatPos &goingPos, Catfish *targetFood)
    {
        auto eventInScope = m_Scene->GetFieldEventManager()->UseEvent();
        eventInScope.StartFromHere();

        yield();

        const auto currPos = m_View.GetMatPos();
        const auto distance = goingPos.CalcManhattan(currPos);

        constexpr double duration = 0.3;
        auto animation = m_Scene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetModel())
                ->AnimPosition(goingPos.GetVec().CastTo<double>() * FieldManager::PixelPerMat, duration * distance)
                ->ToWeakPtr();

        coroUtil::WaitForExpire(yield, animation);

        targetFood->Destroy();

        searchCatfishEveryAngle(m_Scene, nullptr);
    }
} // inGame
