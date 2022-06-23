//
// Created by sashi0034 on 2022/05/07.
//

#include "Graph.h"
#include <SDL_image.h>
#include "log.h"
#include <cassert>
#include "GraphBlend.h"

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

    void Graph::RenderGraph(
            const SDL_Renderer *renderer,
            const Vec2<int> &startPoint,
            const Rect<int> &srcRect,
            Vec2<double> scale,
            double rotationDeg,
            bool isFlipHorizontal,
            const GraphBlend &blend)
    {
        const auto srcRectSize = const_cast<Rect<int> &>(srcRect).GetSize();
        const auto screenSize = Vec2<double>{srcRectSize.X * scale.X, srcRectSize.Y * scale.Y}.CastTo<int>();
        SDL_Rect drawingToScreenRect = SDL_Rect{startPoint.X, startPoint.Y, screenSize.X, screenSize.Y};
        SDL_Rect cutSrcRect = SDL_Rect{srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height};

        SDL_SetTextureBlendMode(m_Texture, blend.GetMode());
        SDL_SetTextureAlphaMod(m_Texture, blend.GetPal());

        SDL_RenderCopyEx(const_cast<SDL_Renderer *>(renderer), m_Texture, &cutSrcRect, &drawingToScreenRect,
                         rotationDeg, nullptr, isFlipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    Graph *Graph::CreateFromFilePath(SDL_Renderer *renderer, const std::string &filePath)
    {
        auto surface = IMG_Load(filePath.c_str());
        assert(surface);

        return new Graph(renderer, surface);
    }

}
