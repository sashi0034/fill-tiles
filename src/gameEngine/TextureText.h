//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_TEXTURETEXT_H
#define FILL_TILES_TEXTURETEXT_H

#include "SpriteTexture.h"
#include "FontResource.h"

namespace gameEngine
{
    class TextureText
    {
    public:
        explicit TextureText(FontResource *font);
        void SetForeground(EasyRgba color);
        void SetOutline(EasyRgba color);
        void ChangeText(const std::string& text);
        SpriteTexture& GetTexture();
    private:
        TextureText() = default;
        FontResource* m_Font;
        SpriteTexture m_Texture = SpriteTexture::Create();
        unique_ptr<Graph> m_TextGraph{};
        EasyRgba m_Foreground = EasyRgba(255, 255, 255);
        EasyRgba m_Outline = EasyRgba(32, 32, 32);
    };

} // gameEngine

#endif //FILL_TILES_TEXTURETEXT_H
