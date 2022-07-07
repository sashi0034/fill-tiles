//
// Created by sashi0034 on 2022/07/07.
//

#include "util.h"

namespace inGame
{
    void util::SetTextureByCenter(SpriteTexture &texture, const Vec2<double> &pos)
    {
        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();
        texture.SetPosition(pos - size / 2.0);
    }

    Vec2<double> util::GetTextureCentralPos(SpriteTexture &texture)
    {
        const auto pos = texture.GetPosition();

        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();

        return pos + size / 2.0;
    }
}


