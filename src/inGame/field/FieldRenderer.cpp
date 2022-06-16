//
// Created by sashi0034 on 2022/06/16.
//

#include "FieldRenderer.h"
#include "../FieldManager.h"

namespace inGame::field
{
    const int FieldRenderer::pixelPerChip = FieldManager::PixelPerChip;

    FieldRenderer::FieldRenderer(const resource::Image *image, const Vec2<int> &matPos,
                                 const Vec2<int> &screenPos, SDL_Renderer *renderer, const Vec2<int> &srcSize,
                                 const Vec2<double> &pixelScaleSize, ITileMap *tileMap)
            : m_ResImage(image),
              m_MatPos(matPos),
              m_ScreenPos(screenPos),
              m_Renderer(renderer),
              m_SrcSize(srcSize),
              m_PixelScaleSize(pixelScaleSize),
              m_TileMapPtr(tileMap)
    {}

    bool FieldRenderer::RenderChip(ETileKind kind)
    {
        // @todo: tileKindでswitch
        // @todo: まずはnormal_plateau_16x16.pngを描画したい
        // @todo: https://github.com/sashi0034/min-rpg/blob/master/ingame_manager.cpp#:~:text=FieldLayerBase%3A%3AdrawingAutoTile


        switch (kind)
        {
            case ETileKind::normal_plateau:
                renderAutoTile(m_ResImage->normal_plateau_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::normal_plateau);
                });
                break;
            case ETileKind::normal_plateau_cliff:
                renderPlateauCliff(m_ResImage->normal_plateau_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::normal_plateau_cliff);
                });
                break;
            default:
                return false;
        }

        return true;
    }


    void FieldRenderer::renderAutoTile(Graph *image, const std::function<bool(int, int)> &isNeighbor,  const Vec2<int> &targetSrcOrigin)
    {
        static const Vec2<int> srcStartingPoints[16] = {
                Vec2{0, 0} * pixelPerChip, //
                Vec2{0, 1} * pixelPerChip, //       D
                Vec2{2, 3} * pixelPerChip, //     U
                Vec2{2, 2} * pixelPerChip, //     U D
                Vec2{1, 0} * pixelPerChip, //   R
                Vec2{1, 1} * pixelPerChip, //   R   D
                Vec2{1, 3} * pixelPerChip, //   R U
                Vec2{1, 2} * pixelPerChip, //   R U D
                Vec2{3, 0} * pixelPerChip, // L
                Vec2{3, 1} * pixelPerChip, // L     D
                Vec2{3, 3} * pixelPerChip, // L   U
                Vec2{3, 2} * pixelPerChip, // L   U D
                Vec2{2, 0} * pixelPerChip, // L R
                Vec2{2, 1} * pixelPerChip, // L R   D
                Vec2{2, 3} * pixelPerChip, // L R U
                Vec2{2, 2} * pixelPerChip, // L R U D
        };

        const int srcStartingIndex =
                (int(isNeighbor(m_MatPos.X - 1, m_MatPos.Y)) << 3) +
                (int(isNeighbor(m_MatPos.X + 1, m_MatPos.Y)) << 2) +
                (int(isNeighbor(m_MatPos.X, m_MatPos.Y - 1)) << 1) +
                (int(isNeighbor(m_MatPos.X, m_MatPos.Y + 1)) << 0);

        const auto &srcStarting = srcStartingPoints[srcStartingIndex];

        image->RenderGraph(
                m_Renderer,
                m_ScreenPos, Rect<int>{srcStarting + targetSrcOrigin, m_SrcSize},
                m_PixelScaleSize);
    }

    void FieldRenderer::renderPlateauCliff(Graph *image, const std::function<bool(int, int)> &isNeighbor)
    {
        static const Vec2<int> srcStartingPoints[4] = {
                Vec2{0, 4} * pixelPerChip, //
                Vec2{1, 4} * pixelPerChip, //   R
                Vec2{3, 4} * pixelPerChip, // L
                Vec2{2, 4} * pixelPerChip, // L R
        };

        const int srcStartingIndex =
                (int(isNeighbor(m_MatPos.X - 1, m_MatPos.Y)) << 1) +
                (int(isNeighbor(m_MatPos.X + 1, m_MatPos.Y)) << 0);

        const auto &srcStarting = srcStartingPoints[srcStartingIndex];

        image->RenderGraph(
                m_Renderer,
                m_ScreenPos, Rect<int>{srcStarting, m_SrcSize},
                m_PixelScaleSize);
    }

    bool FieldRenderer::isNeighbor(int x, int y, ETileKind kind) const
    {
        return m_TileMapPtr->HasChipAt(Vec2{x, y}, kind) == Boolean::True;
    }


}
