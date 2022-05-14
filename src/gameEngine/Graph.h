//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_GRAPH_H
#define FILL_TILES_GRAPH_H

#include <SDL.h>
#include <memory>
#include "Vec2.h"
#include "Rect.h"

using std::unique_ptr;
using std::shared_ptr;

namespace gameEngine
{
    class Graph
    {
        std::unique_ptr<SDL_Surface> m_Surface = nullptr;
        std::unique_ptr<SDL_Texture> m_Texture = nullptr;
    public:
        Graph(std::unique_ptr<SDL_Surface> surface, std::unique_ptr<SDL_Texture> texture);
        ~Graph();
        [[nodiscard]] const SDL_Texture& GetTexture() const;
        void RenderGraph(SDL_Renderer* renderer, const Vec2<int>* startPoint, const Rect<int>* srcRect, double scale);
        void RenderGraph(SDL_Renderer* renderer, const Vec2<int>* startPoint, const Rect<int>* srcRect, double scale, double rotationDeg);
        void RenderGraph(SDL_Renderer* renderer, const Vec2<int>* startPoint, const Rect<int>* srcRect, double scale, double rotationDeg, bool isFlip);
    };
}


#endif //FILL_TILES_GRAPH_H
