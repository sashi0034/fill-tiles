//
// Created by sashi0034 on 2022/07/01.
//

#include "TalkingBalloon.h"
#include "MainScene.h"
#include "ZIndex.h"
#include "LuaEngine.h"

namespace inGame{

    TalkingBalloon::TalkingBalloon(IMainScene *scene, const std::string &text, const Vec2<double> &pos) :
          ActorBase(scene->GetEffectManager()->GetChildren()),
          m_Scene(scene),
          m_Text(text),
          m_TextPassage(scene->GetRoot()->GetAppState(),
                        scene->GetRoot()->RscFont->KHDotAkihabara32px.get(), Rgba(255, 255, 255), Rgba(16, 16, 16))
    {
        m_SpriteRoot.SetPosition(pos);
        scene->GetScrollManager()->RegisterSprite(m_SpriteRoot);
        initBackground(scene);
        initTextPassage();
        scene->GetEffectManager()->GetCoroutineManager()->Start(new CoroTaskCall(
                [&](auto&& yield){this->startAppear(yield); }
                ));
    }

    void TalkingBalloon::initBackground(IMainScene *scene)
    {
        const auto sideRatio = Vec2{0.1, 0.1};

        m_Background = std::make_unique<NinePatchImage>(
                scene->GetRoot()->GetAppState(),
                scene->GetRoot()->RscImage->ui_gray_rounnd_rect.get(),
                Vec2{0.0, 0.0}, Vec2<double>{bgSize.X, bgSize.Y}, sideRatio);
        m_Background->GetSprite().SetBlend(GraphBlend(200));
        m_Background->GetSprite().SetPositionParent(m_SpriteRoot);
        m_Background->GetSprite().SetScale(Vec2{0.0, 1.0});
    }


    void TalkingBalloon::initTextPassage()
    {
        m_TextPassage.SetPos(bgSize/2.0);
        m_TextPassage.SetAlignment(ETextHorizontalAlign::Center, ETextVerticalAlign::Center);
        m_TextPassage.SetZIndex(1);
        m_TextPassage.SetPositionParent(m_Background->GetSprite());
        m_TextPassage.UpdateTextAndView("");
    }


    CoroTask TalkingBalloon::startAppear(CoroTaskYield &yield)
    {
        yield();
        constexpr double duration = 0.3;

        auto scaling = m_Scene->GetEffectManager()->GetAnimator()->TargetTo(m_Background->GetSprite())
                ->AnimScale(Vec2{1.0, 1.0}, duration)->SetEase(EAnimEase::OutBack)->ToWeakPtr();
        coroUtil::WaitForExpire(yield, scaling);

        std::string currStr{};

        sol::table multiByteChar = m_Scene->GetRoot()->GetLua()->GetState()["MultiByteChar"];
        int textLength = multiByteChar["Length"](m_Text);

        bool isInTag = false;

        for (int i=0; i<textLength; ++i)
        {
            std::string nextStr = multiByteChar["GetAt"](m_Text, i);

            if (!isInTag && nextStr=="<") isInTag = true;
            if (isInTag && nextStr==">") isInTag = false;

            currStr += nextStr;
            m_TextPassage.UpdateTextAndView(currStr);

            if (isInTag) continue;

            constexpr int guruGuruTemp = 5;
            if (i % guruGuruTemp == 0) performAnimGuruGuruChar(yield, duration / 10.0, currStr);

            coroUtil::WaitForTime(yield, m_Text[i]!='>' ? duration/10.0 : duration);
        }

        coroUtil::WaitForTime(yield, duration * 7);

        getBelongingPool()->Destroy(this);
    }

    void TalkingBalloon::performAnimGuruGuruChar(CoroTaskYield &yield, const double duration, std::string &currStr)
    {
        currStr += " ";

        for (int count=0; count < 4; count++)
        {
            char animChar = ' ';
            switch (count % 4)
            {
                case 0:
                    animChar = '|'; break;
                case 1:
                    animChar = '/'; break;
                case 2:
                    animChar = '-'; break;
                case 3:
                    animChar = '\\'; break;
            }
            currStr[currStr.length()-1] = animChar;

            m_TextPassage.UpdateTextAndView(currStr);
            coroUtil::WaitForTime(yield, duration);
        }

        currStr.pop_back();
        m_TextPassage.UpdateTextAndView(currStr);
    }


    TalkingBalloon* TalkingBalloon::Create(IMainScene *scene, const std::string &text, const MatPos &pos)
    {
        auto effectManager = scene->GetEffectManager()->GetChildren();
        auto product = new TalkingBalloon(scene, text, pos.ToPixelPos() + FieldManager::MatPixelSize.CastTo<double>() / 2.0 +
                Vec2<double>(0, -bgSize.Y/2.0 - FieldManager::PixelPerMat));
        effectManager->Birth(product);
        return product;
    }

}