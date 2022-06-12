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
        auto renderingGraph =renderingSpr->GetGraph();
        if (renderingGraph == nullptr) return;
        if (!renderingSpr->GetVisible() || !renderingSpr->GetParentalVisibility()) return;

        auto blend = renderingSpr->GetBlend();
        double rotationDeg = renderingSpr->GetRotationDeg();
        bool isFlip = renderingSpr->GetFlip();

        auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();
        const Vec2<int> screenPos = (globalPos * appState->GetPixelPerUnit()).EachTo<int>();

        SDL_Renderer* renderer = appState->GetRenderer();
        auto srcRect = renderingSpr->GetSrcRect();


        renderingGraph->RenderGraph(renderer, screenPos, srcRect, double(scale), rotationDeg, isFlip, blend);
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
