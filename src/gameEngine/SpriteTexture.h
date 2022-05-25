//
// Created by sashi0034 on 2022/05/13.
//

#ifndef FILL_TILES_SPRITETEXTURE_H
#define FILL_TILES_SPRITETEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Vec2.h"
#include <vector>
#include <functional>
#include "Graph.h"
#include "GraphBlend.h"
#include "AppState.h"
#include "renderingProcess.h"
#include "Sprite.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

namespace gameEngine
{
    class Sprite;

    class SpriteTexture
    {
        static std::vector<weak_ptr<SpriteTexture>> spriteTexturePool;

        weak_ptr<Sprite> m_OwnerSprite{};
        Vec2<double> m_Position{0, 0};
        weak_ptr<SpriteTexture> m_PositionParent{};
        double m_Z;
        Graph* m_Graph;
        Rect<int> m_SrcRect{0, 0, 0, 0};
        double m_Scale = 1.0;
        bool m_IsFlip = false;
        double m_RotationDeg = 0;
        GraphBlend m_Blend{};
        bool m_IsVisible = true;
        weak_ptr<SpriteTexture> m_VisibilityParent{};

        std::function<void(IAppState*)> m_RenderingProcess;

        static void collectGarbageInSpriteTexturePool(std::vector<int> &garbageIndexes);

        SpriteTexture();
        SpriteTexture(shared_ptr<Sprite>& ownerSpr, Graph* graph, Rect<int>& srcRect);
    public:
        static shared_ptr<SpriteTexture> Create(shared_ptr<Sprite>& ownerSpr, Graph* graph);
        static shared_ptr<SpriteTexture> Create(shared_ptr<Sprite>& ownerSpr, Graph* graph, Rect<int>& srcRect);

        void SetPosition(const Vec2<double>& pos);
        [[nodiscard]] Vec2<double> GetPosition() const;

        void SetZ(double z);
        [[nodiscard]] double GetZ() const;

        void SetGraph(Graph* graph);
        [[nodiscard]] Graph* GetGraph() const;

        void SetSrcRect(const Rect<int>& srcRect);
        void SetSrcRect(const Vec2<int>& startingPoint);
        [[nodiscard]] Rect<int> GetSrcRect() const;

        void SetScale(double scale);
        [[nodiscard]] double GetScale() const;

        void SetFlip(bool isFlip);
        [[nodiscard]] bool GetFlip() const;

        void SetPositionParent(const shared_ptr<SpriteTexture>& parent);
        [[nodiscard]] weak_ptr<SpriteTexture> GetPositionParent() const;

        void SetVisible(bool isVisible);
        [[nodiscard]] bool GetVisible() const;

        void SetVisibilityParent(const shared_ptr<SpriteTexture>& parent);
        [[nodiscard]] weak_ptr<SpriteTexture> GetVisibilityParent() const;

        void SetRotationDeg(double deg);
        [[nodiscard]] double GetRotationDeg() const;

        void SetBlend(GraphBlend& blend);
        [[nodiscard]] GraphBlend GetBlend() const;

        void SetRenderingProcess(const std::function<void(IAppState*)>& process);

        Vec2<double> GetParentalGlobalPosition();
        bool GetParentalVisibility();

        static void RenderAll(IAppState* appState);
    };
}


#endif //FILL_TILES_SPRITETEXTURE_H
