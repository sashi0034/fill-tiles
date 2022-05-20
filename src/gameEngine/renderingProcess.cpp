//
// Created by sashi0034 on 2022/05/18.
//

#include "renderingProcess.h"
#include <SDL.h>
#include <SDL_image.h>

namespace gameEngine::renderingProcess
{
    void RenderSprite(AppState &appState, SpriteTexture *renderingSpr, double scale)
    {
        auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();

        const Vec2<int> screenPos = (globalPos * appState.GetPixelPerUnit()).EachTo<int>();

        const SDL_Renderer &renderer = appState.GetRenderer();
        auto srcRect = renderingSpr->GetSrcRect();

        renderingSpr->GetGraph()->RenderGraph(&renderer, &screenPos, &srcRect, double(scale));
    }

    void RenderSpriteAlignToUnit(AppState &appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, appState.GetPixelPerUnit());
    }

    void RenderSpriteDotByDot(AppState &appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, 1);
    }

    void RenderSpriteTwoDots(AppState &appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, 2);
    }
}
