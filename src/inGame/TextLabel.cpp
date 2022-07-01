//
// Created by sashi0034 on 2022/07/01.
//

#include "TextLabel.h"
namespace inGame{

    TextLabel::TextLabel(IChildrenPool<ActorBase> *parentPool, IAppState *app) :ActorBase(parentPool)
    {
        const char* fontPath = "assets/fonts/PixelMplus-20130602/PixelMplus12-Regular.ttf";
        constexpr int fontSize = 24;

        TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
        if (!font) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
        TTF_Font* fontOutlined = TTF_OpenFont(fontPath, fontSize);
        if (!fontOutlined) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
        const int outline = 2;
        TTF_SetFontOutline(fontOutlined, outline);

        //todo: TTF_CloseFont()

        m_Surface = TTF_RenderUTF8_Blended(font, "Hello World! なのです!", SDL_Color{255,255,255,255});
        m_SurfaceOutlined = TTF_RenderUTF8_Blended(fontOutlined, "Hello World! なのです!", SDL_Color{20,20,20,255});
        auto destRect = SDL_Rect{outline, outline, m_Surface->w, m_Surface->h};
        SDL_SetSurfaceBlendMode(m_Surface, SDL_BLENDMODE_BLEND);
        SDL_BlitSurface(m_Surface, nullptr, m_SurfaceOutlined, &destRect);
        //SDL_FreeSurface(m_Surface);

        m_Texture = SDL_CreateTextureFromSurface(app->GetRenderer(), m_Surface);
        m_TextureOutlined = SDL_CreateTextureFromSurface(app->GetRenderer(), m_SurfaceOutlined);

        m_Sprite.SetRenderingProcess([&](IAppState* app){
            // 文字を描写したTextureのサイズを取得する
            int iw, ih;
            SDL_QueryTexture(m_TextureOutlined, NULL, NULL, &iw, &ih);

            SDL_Rect txtRect = SDL_Rect{0, 0, iw, ih};
            SDL_Rect pasteRect = SDL_Rect{200, 200, iw, ih};

            // Textureを描写する
            // 描写元の描写する部分,描写先の描写する部分)
            // サイズが違うと勝手にTextureを伸展してくれる
            SDL_RenderCopy(app->GetRenderer(), m_TextureOutlined, &txtRect, &pasteRect);
            //SDL_RenderCopy(app->GetRenderer(), m_Texture, &txtRect, &pasteRect);





            SDL_QueryTexture(m_Texture, NULL, NULL, &iw, &ih);

            txtRect = SDL_Rect{0, 0, iw, ih};
            pasteRect = SDL_Rect{200,250, iw, ih};

            // Textureを描写する
            // 描写元の描写する部分,描写先の描写する部分)
            // サイズが違うと勝手にTextureを伸展してくれる
            SDL_RenderCopy(app->GetRenderer(), m_Texture, &txtRect, &pasteRect);
            //SDL_RenderCopy(app->GetRenderer(), m_Texture, &txtRect, &pasteRect);
        });
    }

}