//
// Created by sashi0034 on 2022/05/07.
//

#include "Graph.h"
#include <SDL_image.h>
#include "log.h"
#include <cassert>

namespace gameEngine
{
    Graph::Graph(SDL_Renderer* renderer, SDL_Surface *surface)
    {
        assert(renderer);
        assert(surface);
        m_Surface = surface;
        m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
    }

    Graph::Graph(SDL_Surface *surface, SDL_Texture* texture)
    {
        assert(surface);
        assert(texture);
        m_Surface = surface;
        m_Texture =texture;
    }

    Graph::~Graph()
    {
        if (m_Surface != nullptr) SDL_FreeSurface(m_Surface);
        if (m_Texture != nullptr) SDL_DestroyTexture(m_Texture);
    }

    const SDL_Texture* Graph::GetTexture() const
    {
        return m_Texture;
    }

    void Graph::RenderGraph(const SDL_Renderer *renderer, const Vec2<int> &startPoint,
                            const Rect<int> &srcRect, double scale)
    {
        RenderGraph(renderer, startPoint, srcRect, scale, 0, false);
    }

    void Graph::RenderGraph(const SDL_Renderer *renderer, const Vec2<int> &startPoint,
                            const Rect<int> &srcRect, double scale,
                            double rotationDeg)
    {
        RenderGraph(renderer, startPoint, srcRect, scale, rotationDeg, false);
    }

    void Graph::RenderGraph(const SDL_Renderer *renderer, const Vec2<int> &startPoint,
                            const Rect<int> &srcRect, double scale,
                            double rotationDeg, bool isFlip)
    {
        auto screenSize = const_cast<Rect<int>&>(srcRect).GetSize() * scale;
        SDL_Rect drawingToScreenRect = SDL_Rect{startPoint.X, startPoint.Y, screenSize.X, screenSize.Y};
        SDL_Rect cutSrcRect = SDL_Rect{srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height};

        const SDL_Point centerPoint{srcRect.Width / 2, srcRect.Height / 2};
        SDL_RenderCopyEx(const_cast<SDL_Renderer*>(renderer), m_Texture, &cutSrcRect, &drawingToScreenRect,
                         rotationDeg, &centerPoint, isFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

}
