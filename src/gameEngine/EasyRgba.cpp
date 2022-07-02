//
// Created by sashi0034 on 2022/07/02.
//

#include "EasyRgba.h"
#include "Range.h"

namespace gameEngine
{
    EasyRgba::EasyRgba(int r, int g, int b)
    : m_R(r), m_G(g), m_B(b)
    {}

    EasyRgba::EasyRgba(int r, int g, int b, int alpha)
    : m_R(r), m_G(g), m_B(b), m_Alpha(alpha)
    {}

    EasyRgba &EasyRgba::MakeInRange()
    {
        m_R = colorRange.MakeInRange(m_R);
        m_G = colorRange.MakeInRange(m_G);
        m_B = colorRange.MakeInRange(m_B);
        m_Alpha = colorRange.MakeInRange(m_Alpha);

        return *this;
    }

    SDL_Color EasyRgba::GetSdlColor() const
    {
        assert(colorRange.IsBetween(m_R));
        assert(colorRange.IsBetween(m_G));
        assert(colorRange.IsBetween(m_B));
        assert(colorRange.IsBetween(m_Alpha));
        return SDL_Color{Uint8(m_R), Uint8(m_G), Uint8(m_B), Uint8(m_Alpha)};
    }
} // gameEngine
