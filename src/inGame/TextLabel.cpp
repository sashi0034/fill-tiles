//
// Created by sashi0034 on 2022/07/01.
//

#include "TextLabel.h"
namespace inGame{

    TextLabel::TextLabel(IChildrenPool<ActorBase> *parentPool, GameRoot *root)
        : ActorBase(parentPool), m_Text(root->ResFont->PixelMPlus24Px.get())
    {
        //const char* fontPath = "assets/fonts/Mplus2-Regular.ttf";

       m_Text.ChangeText("Hello Hello. ラベルテストです。 12345");

        m_Text.GetTexture().SetPosition(Vec2<double>{120, 20});
    }

}