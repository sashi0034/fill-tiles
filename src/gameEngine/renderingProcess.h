//
// Created by sashi0034 on 2022/05/18.
//

#ifndef FILL_TILES_RENDERINGPROCESS_H
#define FILL_TILES_RENDERINGPROCESS_H

#include "SDL.h"
#include "SDL_image.h"
#include "SpriteTexture.h"

namespace gameEngine{
    class SpriteTexture;
}

namespace gameEngine::renderingProcess
{

    void RenderSprite(AppState& appState, SpriteTexture* renderingSpr, double scale);
    void RenderSpriteAlignToUnit(AppState& appState, SpriteTexture* renderingSpr);
    void RenderSpriteDotByDot(AppState& appState, SpriteTexture* renderingSpr);
    void RenderSpriteTwoDots(AppState& appState, SpriteTexture* renderingSpr);
}


#endif //FILL_TILES_RENDERINGPROCESS_H
