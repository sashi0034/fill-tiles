//
// Created by sashi0034 on 2022/07/01.
//

#include "TextLabel.h"
#include "MainScene.h"
#include "ZIndex.h"
#include "effect/Smoke.h"

namespace inGame{

    TextLabel::TextLabel(IChildrenPool<ActorBase> *parentPool, IMainScene *scene)
        : ActorBase(parentPool), m_Scene(scene),
          m_TextList(scene->GetRoot()->GetAppState(), scene->GetRoot()->ResFont->KHDotAkihabara32px.get(), Rgba(255, 255, 255), Rgba(40, 40, 255))
    {
        m_Background = std::make_unique<NinePatchImage>(
                scene->GetRoot()->GetAppState(),
                scene->GetRoot()->ResImage->ui_white_rounnd_rect.get(),
                Vec2{100.0, 100.0}, Vec2{200.0, 80.0}, Vec2{0.1, 0.1});
        m_Background->GetSprite().SetBlend(GraphBlend(120));

        m_TextList.SetPositionParent(m_Background->GetSprite());
        m_TextList.SetPos(Vec2 < double > {100, 40});
        m_TextList.SetAlignment(ETextHorizontalAlign::Center, ETextVerticalAlign::Center);
        m_TextList.SetZIndex(1);
        m_TextList.UpdateTextAndView("おてんとうさま<br>これは ABCDE 012345 です。<br>眠すぎ<br>おねんね");
    }

    void TextLabel::Init()
    {
        effect::Smoke::Produce(m_Scene->GetEffectManager(), Vec2<double>{200, 150});
    }

}