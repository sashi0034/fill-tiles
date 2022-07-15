//
// Created by sashi0034 on 2022/07/13.
//

#include "Fairy.h"
#include "../ZIndex.h"
#include "../Player.h"
#include "../TalkingBalloon.h"

namespace inGame::character
{

    Fairy::Fairy(IMainScene *mainScene, const MatPos &matPos, const std::string &message)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->blobwob_24x24.get())
    {
        const int pixelPerMat = FieldManager::PixelPerMat;
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellSrcSize});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSrcSize.X - pixelPerMat) / 2.0, double(cellSrcSize.Y - pixelPerMat)});

        m_View.SetCollider(mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        ZIndexCharacter(m_View).ApplyZ();

        auto player = mainScene->GetPlayer();
        if (player!= nullptr)
        {
            subscribePlayerMove(mainScene, matPos, message, player);
        }

        std::cout << message << std::endl;


        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView().GetWeakPtr())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 0}, 0.2)
                ->AddFrame(Vec2{1, 0}, 0.1)
                ->AddFrame(Vec2{2, 0}, 0.2)
                ->AddFrame(Vec2{3, 0}, 0.1)
                ->AddFrame(Vec2{4, 0}, 0.2)
                ->AddFrame(Vec2{5, 0}, 0.1)
                ->AddFrame(Vec2{6, 0}, 0.2)
                ->AddFrame(Vec2{7, 0}, 0.1)
                ->AddFrame(Vec2{8, 0}, 0.2)
                ->AddFrame(Vec2{9, 0}, 0.4);
    }

    void Fairy::subscribePlayerMove(IMainScene *mainScene, const MatPos &matPos, const std::string &message,
                                    const Player *player)
    {
        player->OnMoveFinish().subscribe([&, matPos, message, mainScene](PlayerMoveData *moveData) {
            m_View.GetView().SetFlip(moveData->BeforePos.GetVec().X > matPos.GetVec().X);

            constexpr int talkAbleDistance = 3;

            bool isJustInTalkAbleRange =
                    matPos.CalcManhattan(moveData->AfterPos) <= talkAbleDistance &&
                    matPos.CalcManhattan(moveData->BeforePos) > talkAbleDistance;
            
            if (m_TalkingRef.IsNull() && isJustInTalkAbleRange)
                m_TalkingRef = TalkingBalloon::Create(mainScene, message, matPos)->GetWeakPtr();

        });
    }
}