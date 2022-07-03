//
// Created by sashi0034 on 2022/07/01.
//

#include "TextLabel.h"
#include "MainScene.h"
#include "ZIndex.h"

namespace inGame{

    TextLabel::TextLabel(IChildrenPool<ActorBase> *parentPool, IMainScene *scene)
        : ActorBase(parentPool), m_Text(scene->GetRoot()->ResFont->PixelMPlus24Px.get())
    {
        //const char* fontPath = "assets/fonts/Mplus2-Regular.ttf";

        m_Text.ChangeText("Hello Hello. ラベルテストです。 12345");
        ZIndexUi(&m_Text.GetTexture()).SetIndex(1).ApplyZ();


        m_Text.GetTexture().SetPosition(Vec2<double>{80, 50});

        m_Background = std::make_unique<NinePatchImage>(
                scene->GetRoot()->GetAppState(),
                scene->GetRoot()->ResImage->ui_black_window.get(),
                Vec2{100.0, 100.0}, Vec2{120.0, 120.0}, Vec2{0.05, 0.05});
    }

}