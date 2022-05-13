//
// Created by sashi0034 on 2022/05/13.
//

#ifndef FILL_TILES_SPRITETEXTURE_H
#define FILL_TILES_SPRITETEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Vec2.h"
#include <vector>
#include <functional>
#include "Graph.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

namespace gameEngine
{
    class SpriteTexture
    {
        static std::vector<shared_ptr<SpriteTexture>> spriteTexturePool;

        Vec2<double> m_Position{0, 0};
        double m_Z;
        weak_ptr<Graph> m_Graph{};
        Rect<int> m_SrcRect{0, 0, 0, 0};
        double m_Scale = 1.0;
        bool m_IsFlip = false;
        const weak_ptr<SpriteTexture> m_ParentPosition{};
        double m_RotationDeg = 0;
        int m_BlendMode = SDL_BLENDMODE_BLEND;
        int m_BlendPal = 255;

        std::function<void()> m_RenderingProcess = [](){};
    public:
        SpriteTexture(shared_ptr<Graph> graph);
        SpriteTexture(shared_ptr<Graph> graph, Rect<int>& srcRect);
    };
}


#endif //FILL_TILES_SPRITETEXTURE_H
