//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_TEXTLABEL_H
#define FILL_TILES_TEXTLABEL_H

#include "SDL_ttf.h"
#include "ActorBase.h"
#include "GameRoot.h"
#include "MainScene.h"
#include "NinePatchImage.h"
#include "TextController.h"

namespace inGame
{
    class TextLabel : public ActorBase
    {
    public:
        TextLabel(IChildrenPool<ActorBase> *parentPool, IMainScene *scene);
    private:
        TextureText m_Text;
        TextureText m_Text2;
        unique_ptr<NinePatchImage> m_Background;

        TextController m_TextList;
    };
}


#endif //FILL_TILES_TEXTLABEL_H
