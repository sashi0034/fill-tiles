//
// Created by sashi0034 on 2022/08/17.
//

#include "GrowingChick.h"
#include "../Player.h"
#include "../ZIndex.h"
#include "../effect/TextureScrapping.h"

namespace inGame::character
{
    using growth = EGrowingChickGrowth;

    const int pixelPerMat = FieldManager::PixelPerMat;

    GrowingChick::GrowingChick(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
              m_Scene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->egg_16x16.get())
    {

        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, childCellSrcSize});

        m_View.SetModelPos(matPos);

        setViewPos(eggCellSrcSize);

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        animWhenEgg();

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayerMove(mainScene, player);
        }
    }

    void GrowingChick::setViewPos(const Vec2<int>& cellSize)
    {
        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSize.X - pixelPerMat) / 2.0, double(cellSize.Y - pixelPerMat)});
    }

    void GrowingChick::animWhenEgg()
    {
        constexpr double duration = 0.2;
        m_AnimationRef = animator->TargetTo(m_View.GetView())
                ->AnimGraph(childCellSrcSize)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, duration * 4)
                ->AddFrame(Vec2{1, 0}, duration)
                ->AddFrame(Vec2{2, 0}, duration)
                ->AddFrame(Vec2{3, 0}, duration)
                ->ToWeakPtr();
    }

    void GrowingChick::Update(IAppState*)
    {
        ZIndexCharacter(m_View).ApplyZ();
    }

    void GrowingChick::subscribePlayerMove(IMainScene *mainScene, const Player *player)
    {
        player->OnMoveFinish().subscribe([mainScene, this](PlayerMoveData* moveData){
            if (m_Growth!=growth::Egg) return;

            constexpr double nearDistance = 3;
            if (moveData->AfterPos.CalcManhattan(m_View.GetMatPos())>nearDistance) return;
            mainScene->GetFieldManager()->GetCoroutine()->Start([this](auto&& yield){
                startChildProcess(yield);
            });
        });
    }

    void GrowingChick::startChildProcess(CoroTaskYield &yield)
    {
        auto eventInScope = m_Scene->GetFieldEventManager()->AwaitIfEventExist(yield)->UseEvent();
        eventInScope.StartFromHere();

        yield();

        m_Growth = growth::Child;

        effect::TextureScrapping::Produce(effect::TextureScrappingArgs{
                m_Scene->GetEffectManager(),
                m_View.GetViewModelPos(),
                m_View.GetView().GetSrcRect(),
                m_View.GetView().GetGraph()});

        m_View.GetView().SetGraph(m_Scene->GetRoot()->RscImage->chick_16x16.get());
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, childCellSrcSize});
        setViewPos(childCellSrcSize);

        constexpr double duration = 0.2;
        animator->Destroy(m_AnimationRef);
        m_AnimationRef = animator->TargetTo(m_View.GetView())
                ->AnimGraph(childCellSrcSize)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, duration)
                ->AddFrame(Vec2{1, 0}, duration)
                ->AddFrame(Vec2{2, 0}, duration)
                ->ToWeakPtr();

    }


} // inGame