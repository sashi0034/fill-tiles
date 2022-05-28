//
// Created by sashi0034 on 2022/05/13.
//

#include "SpriteTexture.h"

#include <utility>
#include <cassert>

namespace gameEngine
{
    std::vector<weak_ptr<SpriteTexture>> SpriteTexture::spriteTexturePool = {};

    SpriteTexture::SpriteTexture(shared_ptr<Sprite>& ownerSpr, Graph* graph, Rect<int> &srcRect)
    {
        m_OwnerSprite = ownerSpr;
        m_Graph = graph;
        m_SrcRect = srcRect;
        m_RenderingProcess = [this](IAppState* appState){
            renderingProcess::RenderSpriteAlignToUnit(appState, this);
        };
    }


    shared_ptr<SpriteTexture> SpriteTexture::Create(shared_ptr<Sprite>& ownerSprite, Graph *graph)
    {
        auto srcRect = Rect<int>{0, 0, 0, 0};

        return Create(ownerSprite, graph, srcRect);
    }

    shared_ptr<SpriteTexture> SpriteTexture::Create(shared_ptr<Sprite>& ownerSprite, Graph *graph, Rect<int> &srcRect)
    {
        auto product = shared_ptr<SpriteTexture>(new SpriteTexture(ownerSprite, graph, srcRect));

        spriteTexturePool.push_back(product);

        return shared_ptr<SpriteTexture>(product);
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

    double SpriteTexture::GetScale() const
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

    void SpriteTexture::SetPositionParent(const shared_ptr<SpriteTexture>& parent)
    {
        m_PositionParent = parent;
    }

    weak_ptr<SpriteTexture> SpriteTexture::GetPositionParent() const
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

    void SpriteTexture::SetRenderingProcess(const std::function<void(IAppState*)>& process)
    {
        m_RenderingProcess = process;
    }

    Vec2<double> SpriteTexture::GetParentalGlobalPosition()
    {
        if (auto parent = m_PositionParent.lock())
        {
            auto parentPosition = parent->GetParentalGlobalPosition();
            return parent->m_Position + parentPosition;
        }
        else
        {
            return Vec2<double>{0,0};
        }
    }

    bool SpriteTexture::GetParentalVisibility()
    {
        if (auto parent = m_VisibilityParent.lock())
        {
            bool parentVisibility = parent->GetParentalVisibility();
            return parent->m_IsVisible && parentVisibility;
        }
        else
        {
            return true;
        }
    }


    void SpriteTexture::RenderAll(IAppState*appState)
    {
        std::stable_sort(spriteTexturePool.begin(), spriteTexturePool.end(),[](const weak_ptr<SpriteTexture> &left, const weak_ptr<SpriteTexture> &right) -> bool {
            auto leftShared =left.lock();
            auto rightShared = right.lock();
            return (leftShared ? leftShared->GetZ() : 0.0) > (rightShared ? rightShared->GetZ() : 0.0); });
        std::vector<int> garbageIndexes{};
        int size = spriteTexturePool.size();

        for (int i=0; i < size ; ++i)
            if (auto renderingSpr = spriteTexturePool[i].lock())
            {
                if (renderingSpr == nullptr) continue;

                renderingSpr->m_RenderingProcess(appState);
            }
            else
            {
                garbageIndexes.push_back(i);
            }

        collectGarbageInSpriteTexturePool(garbageIndexes);
    }

    SpriteTexture::SpriteTexture()
    {
        assert(false);
    }

    void SpriteTexture::collectGarbageInSpriteTexturePool(std::vector<int> &garbageIndexes)
    {
        for (int i=garbageIndexes.size()-1; i>=0; --i)
        {
            int index = garbageIndexes[i];
            spriteTexturePool.erase(spriteTexturePool.begin()+index);
        }
    }

    void SpriteTexture::SetVisibilityParent(const shared_ptr<SpriteTexture> &parent)
    {
        m_VisibilityParent = parent;
    }

    weak_ptr<SpriteTexture> SpriteTexture::GetVisibilityParent() const
    {
        return m_VisibilityParent;
    }

    void SpriteTexture::SetVisible(bool isVisible)
    {
        m_IsVisible=isVisible;
    }

    bool SpriteTexture::GetVisible() const
    {
        return m_IsVisible;
    }


}