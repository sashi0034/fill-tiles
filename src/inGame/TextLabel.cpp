//
// Created by sashi0034 on 2022/07/01.
//

#include "TextLabel.h"
#include "MainScene.h"
#include "ZIndex.h"

namespace inGame{

    TextLabel::TextLabel(IChildrenPool<ActorBase> *parentPool, IMainScene *scene)
        : ActorBase(parentPool), m_Text(scene->GetRoot()->ResFont->PixelMPlus24Px.get()),m_Text2(scene->GetRoot()->ResFont->MPlus24Px.get())
    {
        //const char* fontPath = "assets/fonts/Mplus2-Regular.ttf";

        m_Text.ChangeText("Hello Hello. ラベルテストです。6789");
        ZIndexUi(&m_Text.GetTexture()).SetIndex(1).ApplyZ();
        m_Text.GetTexture().SetPosition(Vec2<double>{100, 110});

        m_Text2.ChangeText("Hello Hello. ラベルテストです。 12345");
        ZIndexUi(&m_Text2.GetTexture()).SetIndex(1).ApplyZ();
        m_Text2.GetTexture().SetPosition(Vec2<double>{100, 130});

        m_Background = std::make_unique<NinePatchImage>(
                scene->GetRoot()->GetAppState(),
                scene->GetRoot()->ResImage->ui_white_rounnd_rect.get(),
                Vec2{100.0, 100.0}, Vec2{200.0, 80.0}, Vec2{0.1, 0.1});
        m_Background->GetSprite().SetBlend(GraphBlend(120));
    }

}