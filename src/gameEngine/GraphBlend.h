//
// Created by sashi0034 on 2022/05/14.
//

#ifndef FILL_TILES_GRAPHBLEND_H
#define FILL_TILES_GRAPHBLEND_H

#include <SDL_image.h>

namespace gameEngine
{
    class GraphBlend
    {
        int m_Mode = SDL_BLENDMODE_BLEND;
        int m_Pal = 255;
    public:
        GraphBlend();
        GraphBlend(int pal);
        GraphBlend(int mode, int pal);

        void GetMode(int mode);
        [[nodiscard]] int GetMode() const;

        void SetPal(int pal);
        [[nodiscard]] int GetPal() const;
    };
}


#endif //FILL_TILES_GRAPHBLEND_H
