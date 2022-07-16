//
// Created by sashi0034 on 2022/07/16.
//

#include "RemainingMineUi.h"
#include "ZIndex.h"

namespace inGame
{
    RemainingMineUi::RemainingMineUi(IMainScene *scene, MineFlowerManager *mineFlowerManager)
    : ActorBase(scene->GetEffectManager()->GetChildren()),
        m_SceneRef(scene), m_MineFlowerManagerRef(mineFlowerManager)
    {
        m_SpriteRoot.SetPositionParent(m_SpriteRootParent);
    }


    void RemainingMineUi::Init()
    {
        initBackground(m_SceneRef);
        initText(m_SceneRef, "");

        m_Icon.SetGraph(m_SceneRef->GetRoot()->RscImage->mine_flower_16x16.get());
        m_Icon.SetSrcRect(Rect{0, 16, 16, 16});
        m_Icon.SetPositionParent(m_SpriteRoot);
        const Vec2<double> leftMargin{6, 0};
        m_Icon.SetPosition(Vec2{0.0, -8.0} + Vec2<double>{-bgSize.X/2.0, 0} + leftMargin);
        ZIndexUi(&m_Icon).SetIndex(2).ApplyZ();
    }


    void RemainingMineUi::initBackground(IMainScene *scene)
    {
        const auto sideRatio = Vec2{0.1, 0.1};
        m_Background = std::make_unique<NinePatchImage>(
                scene->GetRoot()->GetAppState(),
                scene->GetRoot()->RscImage->ui_black_window.get(),
                Vec2{0.0, 0.0}, Vec2<double>{bgSize.X, bgSize.Y}, sideRatio);
        //m_Background->GetSprite().SetBlend(GraphBlend(200));
        m_Background->GetSprite().SetPositionParent(m_SpriteRoot);
    }

    void RemainingMineUi::initText(IMainScene *scene, const std::string &str)
    {
        const Vec2<double> rightMargin{-6, 0};

        m_TextPassage = std::make_unique<TextPassage>(scene->GetRoot()->GetAppState(),
                                                      scene->GetRoot()->RscFont->KHDotAkihabara32px.get(),
                                                      Rgba(255, 255, 255), Rgba(16, 16, 64));
        m_TextPassage->SetPos(Vec2{bgSize.X, bgSize.Y/2.0} + rightMargin);
        m_TextPassage->SetAlignment(ETextHorizontalAlign::Right, ETextVerticalAlign::Center);
        m_TextPassage->SetZIndex(1);
        m_TextPassage->SetPositionParent(m_Background->GetSprite());
        m_TextPassage->UpdateTextAndView(str);
    }

    void RemainingMineUi::Update(IAppState *appState)
    {
        constexpr double margin = 12;
        m_SpriteRootParent.SetPosition(Vec2{appState->GetScreenSize().X  - margin, margin} + Vec2{-bgSize.X / 2.0, bgSize.Y / 2.0});

        checkUpdateText();
    }

    void RemainingMineUi::checkUpdateText()
    {
        auto&& mineClass = m_MineFlowerManagerRef->GetCurrMineFlowerClass();

        if (mineClass== nullptr) return;

        const int remainingCount = mineClass->GetMineFlowerCount();

        if (remainingCount != m_RemainingCountBefore)
        {
            m_RemainingCountBefore = remainingCount;
            m_SceneRef->GetEffectManager()->GetCoroutineManager()->Start(
                    new CoroTaskCall([&](auto&& yield){ animCountDown(yield, mineClass);}));
        }
    }

    CoroTask RemainingMineUi::animCountDown(CoroTaskYield &yield, MineFlowerClass *mineClass)
    {
        yield();

        const int remainingCount = mineClass->GetMineFlowerCount();
        const int maxRemainingCount = mineClass->GetMaxMineFlowerCount();

        updateText(remainingCount, maxRemainingCount);

        if (remainingCount == 0)
        {
            startAnimCountToZero(yield);
        }
    }

    CoroTask RemainingMineUi::startAnimCountToZero(CoroTaskYield &yield)
    {
        constexpr double enoughBigWidth = 200;
        constexpr double duration = 0.5;

        coroUtil::WaitForTime(yield, duration);

        // 画面外まで動かす
        coroUtil::WaitForExpire(yield,
                                m_SceneRef->GetEffectManager()->GetAnimator()->TargetTo(m_SpriteRoot.GetWeakPtr())
                                        ->AnimPosition(Vec2<double>{enoughBigWidth, 0},
                                                       duration)->SetEase(EAnimEase::OutBack)
                                        ->ToWeakPtr());

        coroUtil::WaitForTrue(yield, [&]() { return !m_SceneRef->GetFieldEventManager()->IsRunning(); });

        auto&& nextMineClass = m_MineFlowerManagerRef->GetNextMineFlowerClass();

        if (nextMineClass== nullptr) return;
        if (nextMineClass->GetMaxMineFlowerCount()==0) return;

        updateText(nextMineClass->GetMineFlowerCount(), nextMineClass->GetMaxMineFlowerCount());

        // 元の位置に戻す
        coroUtil::WaitForExpire(yield,
                                m_SceneRef->GetEffectManager()->GetAnimator()->TargetTo(m_SpriteRoot.GetWeakPtr())
                    ->AnimPosition(Vec2{0.0, 0.0}, duration)->SetEase(EAnimEase::OutBack)
                    ->ToWeakPtr());
    }

    void RemainingMineUi::updateText(const int remainingCount, const int maxRemainingCount)
    {
        std::stringstream stream{};
        stream << remainingCount << " / " << maxRemainingCount;
        m_TextPassage->UpdateTextAndView(stream.str());
    }

} // inGame