//
// Created by sashi0034 on 2022/06/16.
//

#include "FieldRenderer.h"

namespace inGame::field
{
    FieldRenderer::FieldRenderer(const int pixelPerChip, const resource::Image *image, const Vec2<int> &matPos,
                                 const Vec2<int> &screenPos, SDL_Renderer *renderer, const Vec2<int> &srcSize,
                                 const Vec2<double> &pixelScaleSize, ITileMap *tileMap)
            : pixelPerChip(pixelPerChip),
              m_ResImage(image),
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
            case ETileKind::normal_plateau_cliff:
                renderPlateauCliff(m_ResImage->normal_plateau_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::normal_plateau_cliff);});
                break;
            default:
                return false;
        }

        return true;
    }

    void FieldRenderer::renderPlateauCliff(Graph *image, const std::function<bool(int, int)> &isNeighbor)
    {
        static Vec2<int> srcStartingPoints[4] = {
                Vec2{pixelPerChip * 0, pixelPerChip * 2}, //
                Vec2{pixelPerChip * 1, pixelPerChip * 2}, //   R
                Vec2{pixelPerChip * 3, pixelPerChip * 2}, // L
                Vec2{pixelPerChip * 2, pixelPerChip * 2}, // L R
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
