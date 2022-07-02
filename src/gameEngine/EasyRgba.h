//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_EASYRGBA_H
#define FILL_TILES_EASYRGBA_H

#include "SDL.h"
#include "Range.h"
#include <cstddef>

namespace gameEngine
{
    class EasyRgba
    {
    public:
        EasyRgba(int r, int g, int b);
        EasyRgba(int r, int g, int b, int alpha);
        EasyRgba& MakeInRange();
        [[nodiscard]] SDL_Color GetSdlColor() const;

    private:
        static inline const Range<int> colorRange = Range<int>(0, 255);
        int m_R;
        int m_G;
        int m_B;
        int m_Alpha = 255;
    };

} // gameEngine

#endif //FILL_TILES_EASYRGBA_H
