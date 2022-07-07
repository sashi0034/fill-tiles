//
// Created by sashi0034 on 2022/07/07.
//

#include "util.h"

namespace inGame
{
    void util::SetTextureCentral(SpriteTexture &texture, const Vec2<double> &pos)
    {
        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();
        texture.SetPosition(pos + size / 2.0);
    }
}


