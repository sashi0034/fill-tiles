//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_TEXTLABEL_H
#define FILL_TILES_TEXTLABEL_H

#include "SDL_ttf.h"
#include "ActorBase.h"

namespace inGame
{
    class TextLabel : public ActorBase
    {
    public:
        TextLabel(IChildrenPool<ActorBase> *parentPool, IAppState *app);
    private:
        SDL_Surface *m_Surface{};
        SDL_Texture *m_Texture{};
        SDL_Surface *m_SurfaceOutlined{};
        SDL_Texture *m_TextureOutlined{};

        SpriteTexture m_Sprite = SpriteTexture::Create();
    };
}


#endif //FILL_TILES_TEXTLABEL_H
