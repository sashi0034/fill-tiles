//
// Created by sashi0034 on 2022/05/18.
//

#include "renderingProcess.h"
#include <SDL.h>
#include <SDL_image.h>

namespace gameEngine::renderingProcess
{
    void RenderSprite(IAppState*appState, SpriteTexture *renderingSpr, double scale)
    {
        auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();

        const Vec2<int> screenPos = (globalPos * appState->GetPixelPerUnit()).EachTo<int>();

        SDL_Renderer* renderer = appState->GetRenderer();
        auto srcRect = renderingSpr->GetSrcRect();

        renderingSpr->GetGraph()->RenderGraph(renderer, &screenPos, &srcRect, double(scale));
    }

    void RenderSpriteAlignToUnit(IAppState*appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, appState->GetPixelPerUnit());
    }

    void RenderSpriteDotByDot(IAppState*appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, 1);
    }

    void RenderSpriteTwoDots(IAppState*appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, 2);
    }
}
