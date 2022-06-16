//
// Created by sashi0034 on 2022/06/11.
//

#include "FieldManager.h"
#include "GameRoot.h"

namespace inGame
{
    using namespace field;

    FieldManager::FieldManager(IChildrenPool<ActorBase> *parentPool, IAppState *app) :
            ActorBase(parentPool),
            ScreenChipSize(app->GetScreenSize() / PixelPerChip)
    {
        m_TileMap.LoadMapFile("field_00.tmx");

        m_Texture = SpriteTexture::Create(nullptr);
        m_Texture->SetRenderingProcess([this](IAppState *appState) { renderTileMap(appState); });
    }

    void FieldManager::renderTileMap(IAppState *appState)
    {
        const auto globalPos = m_Texture->GetParentalGlobalPosition().EachTo<int>();

        const auto negativeCorrection = Vec2<int>{globalPos.X<0 ? -1 : 0, globalPos.Y<0 ? -1 : 0};

        const Vec2<int> startingChipPoint = (globalPos / PixelPerChip).EachTo<int>() + negativeCorrection;

        const Vec2<int> matSize = m_TileMap.GetMatSize();

        const auto renderingChipStartingPoint = Vec2<int>{
            std::max(0, startingChipPoint.X),
            std::max(0, startingChipPoint.Y)};

        const auto renderingChipEndPoint = Vec2<int>{
                std::min(startingChipPoint.X + ScreenChipSize.X, matSize.X),
                std::min(startingChipPoint.Y + ScreenChipSize.Y, matSize.Y)};

        for (int chipY = renderingChipStartingPoint.Y; chipY<=renderingChipEndPoint.Y; ++chipY)
            for (int chipX = renderingChipStartingPoint.X; chipX<=renderingChipEndPoint.X; ++chipX)
            {
                const auto chipPos = Vec2{chipX, chipY};
                const Vec2<int> renderingScreenPos =
                        globalPos + Vec2{chipX, chipY} * PixelPerChip * appState->GetPixelPerUnit();
                const auto mapElement = m_TileMap.GetElementAt(chipPos);
                const auto chipList = mapElement->GetChipList();

                for (const auto chip : chipList)
                    renderChip(chipPos, renderingScreenPos, appState, chip);
            }
    }

    void FieldManager::renderChip(const Vec2<int> &matPos, const Vec2<int> &screenPos, IAppState *appState,
                                  const TilePropertyChip *chip)
    {
        // @todo: tileKindでswitch
        // @todo: まずはnormal_plateau_16x16.pngを描画したい
        // @todo: https://github.com/sashi0034/min-rpg/blob/master/ingame_manager.cpp#:~:text=FieldLayerBase%3A%3AdrawingAutoTile


        auto srcStarting = chip->SrcPoint;
        const auto& resImage = *GameRoot::GetInstance().ResImage;
        const auto srcSize = Vec2{PixelPerChip, PixelPerChip};
        const double pixelPerUnit = appState->GetPixelPerUnit();
        const auto pixelScaleSize = Vec2<double>{pixelPerUnit, pixelPerUnit};

        switch (chip->Kind)
        {
            case ETileKind::normal_plateau_cliff:
                renderPlateauCliff(matPos, screenPos, appState, resImage.normal_plateau_16x16.get(), srcSize,
                                   pixelScaleSize,
                                   [&](int x, int y) {
                                       return m_TileMap.HasChipAt(Vec2{x, y}, ETileKind::normal_plateau_cliff) ==
                                              Boolean::True;
                                   });
                break;
            default:
                m_TileMap.GetTilesetImage().RenderGraph(
                        appState->GetRenderer(),
                        screenPos, Rect<int>(srcStarting, srcSize),
                        pixelScaleSize);
        }
    }

    void
    FieldManager::renderPlateauCliff(const Vec2<int> &matPos, const Vec2<int> &screenPos, const IAppState *appState,
                                     Graph *image, const Vec2<int> &srcSize, const Vec2<double> &pixelScaleSize,
                                     const std::function<bool(int, int)>& isNeighbor)
    {
        static Vec2<int> srcStartingPoints[4] = {
                Vec2{PixelPerChip * 0, PixelPerChip * 2}, //
                Vec2{PixelPerChip * 1, PixelPerChip * 2}, //   R
                Vec2{PixelPerChip * 3, PixelPerChip * 2}, // L
                Vec2{PixelPerChip * 2, PixelPerChip * 2}, // L R
        };

        const int srcStartingIndex =
                (int(isNeighbor(matPos.X - 1, matPos.Y)) << 1) +
                (int(isNeighbor(matPos.X + 1, matPos.Y)) << 0);

        const auto& srcStarting = srcStartingPoints[srcStartingIndex];

        image->RenderGraph(
                appState->GetRenderer(),
                screenPos, Rect<int>{srcStarting, srcSize},
                pixelScaleSize);
    }
}