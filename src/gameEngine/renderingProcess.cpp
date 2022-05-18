//
// Created by sashi0034 on 2022/05/18.
//

#include "renderingProcess.h"

namespace gameEngine::renderingProcess{
void RenderSprite(AppState& appState, SpriteTexture *renderingSpr, int scale)
{
    auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();

    const Vec2<int> screenPos =(globalPos*appState.GetPixelPerUnit()).EachTo<int>();

    //renderingSpr->GetGraph()->RenderGraph();
}
}
