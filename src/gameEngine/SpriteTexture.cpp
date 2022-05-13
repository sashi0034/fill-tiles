//
// Created by sashi0034 on 2022/05/13.
//

#include "SpriteTexture.h"
namespace gameEngine
{
    SpriteTexture::SpriteTexture(shared_ptr<Graph> graph)
    {
        m_Graph = graph;
    }
    SpriteTexture::SpriteTexture(shared_ptr<Graph> graph, Rect<int> &srcRect)
    {
        m_Graph = graph;
        m_SrcRect = srcRect;
    }
}