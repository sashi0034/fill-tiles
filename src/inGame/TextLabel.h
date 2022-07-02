//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_TEXTLABEL_H
#define FILL_TILES_TEXTLABEL_H

#include "SDL_ttf.h"
#include "ActorBase.h"
#include "GameRoot.h"

namespace inGame
{
    class TextLabel : public ActorBase
    {
    public:
        TextLabel(IChildrenPool<ActorBase> *parentPool, GameRoot *root);
    private:
        TextureText m_Text;
    };
}


#endif //FILL_TILES_TEXTLABEL_H
