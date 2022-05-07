//
// Created by sashi0034 on 2022/05/07.
//

#include "Graph.h"
#include <SDL_image.h>

namespace gameEngine
{
    Graph::Graph(std::unique_ptr<SDL_Surface> surface, std::unique_ptr<SDL_Texture> texture)
    {
        m_Surface = std::move(surface);
        m_Texture = std::move(texture);
    }

    Graph::~Graph()
    {
        if (m_Surface != nullptr) SDL_FreeSurface(m_Surface.get());
        if (m_Texture != nullptr) SDL_DestroyTexture(m_Texture.get());
    }

    std::unique_ptr<SDL_Texture> Graph::GetTexture()
    {
        return std::move(m_Texture);
    }

    void Graph::DrawGraph(SDL_Renderer *renderer, const Vec2<int> *startPoint,
                                      const Rect<int> *srcRect, double scale)
    {
        DrawGraph(renderer, startPoint, srcRect, scale, 0, false);
    }

    void Graph::DrawGraph(SDL_Renderer *renderer, const Vec2<int> *startPoint,
                                      const Rect<int> *srcRect, double scale,
                                      double rotationDeg)
    {
        DrawGraph(renderer, startPoint, srcRect, scale, rotationDeg, false);
    }

    void Graph::DrawGraph(SDL_Renderer *renderer, const Vec2<int> *startPoint,
                                      const Rect<int> *srcRect, double scale,
                                      double rotationDeg, bool isFlip)
    {
        auto screenSize = const_cast<Rect<int> *>(srcRect)->GetSize() * scale;
        SDL_Rect drawingToScreenRect = SDL_Rect{startPoint->X, startPoint->Y, screenSize.X, screenSize.Y};
        SDL_Rect cutSrcRect = SDL_Rect{srcRect->X, srcRect->Y, srcRect->Width, srcRect->Height};

        const SDL_Point centerPoint{srcRect->Width / 2, srcRect->Height / 2};
        SDL_RenderCopyEx(renderer, m_Texture.get(), &cutSrcRect, &drawingToScreenRect,
                         rotationDeg, &centerPoint, isFlip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }
}
