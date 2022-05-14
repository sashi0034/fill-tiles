//
// Created by sashi0034 on 2022/05/13.
//

#include "SpriteTexture.h"

#include <utility>
namespace gameEngine
{
    SpriteTexture::SpriteTexture(Graph* graph) : m_Graph(graph)
    {
        m_Graph = graph;
    }
    SpriteTexture::SpriteTexture(Graph* graph, Rect<int> &srcRect)
    {
        m_Graph = graph;
        m_SrcRect = srcRect;
    }

    void SpriteTexture::SetPosition(const Vec2<double> &pos)
    {
        m_Position = pos;
    }

    Vec2<double> SpriteTexture::GetPosition() const
    {
        return m_Position;
    }

    void SpriteTexture::SetZ(double z)
    {
        m_Z = z;
    }

    double SpriteTexture::GetZ() const
    {
        return m_Z;
    }

    void SpriteTexture::SetGraph(Graph *graph)
    {
        m_Graph = graph;
    }

    Graph *SpriteTexture::GetGraph() const
    {
        return m_Graph;
    }

    void SpriteTexture::SetSrcRect(const Rect<int> &srcRect)
    {
        m_SrcRect = srcRect;
    }

    void SpriteTexture::SetSrcRect(const Vec2<int> &startingPoint)
    {
        m_SrcRect.X = startingPoint.X;
        m_SrcRect.Y = startingPoint.Y;
    }

    Rect<int> SpriteTexture::GetSrcRect() const
    {
        return m_SrcRect;
    }

    void SpriteTexture::SetScale(double scale)
    {
        m_Scale = scale;
    }

    double SpriteTexture::GetScale(double scale) const
    {
        return m_Scale;
    }

    void SpriteTexture::SetFlip(bool isFlip)
    {
        m_IsFlip = isFlip;
    }

    bool SpriteTexture::GetFlip() const
    {
        return m_IsFlip;
    }

    void SpriteTexture::SetPositionParent(const weak_ptr<SpriteTexture>& parent)
    {
        m_PositionParent = parent;
    }

    const weak_ptr<SpriteTexture> SpriteTexture::GetPositionParent() const
    {
        return m_PositionParent;
    }

    void SpriteTexture::SetRotationDeg(double deg)
    {
        m_RotationDeg = deg;
    }

    double SpriteTexture::GetRotationDeg() const
    {
        return m_RotationDeg;
    }

    void SpriteTexture::SetBlend(GraphBlend& blend)
    {
        m_Blend = blend;
    }

    GraphBlend SpriteTexture::GetBlend() const
    {
        return m_Blend;
    }

    void SpriteTexture::SetRenderingProcess(const std::function<void()>& process)
    {
        m_RenderingProcess = process;
    }
}