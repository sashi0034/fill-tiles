//
// Created by sashi0034 on 2022/06/11.
//

#include "FieldManager.h"
#include "GameRoot.h"
#include "field/FieldRenderer.h"

namespace inGame
{
    using namespace field;

    FieldManager::FieldManager(IChildrenPool<ActorBase> *parentPool, IAppState *app) :
            ActorBase(parentPool),
            ScreenMatSize(app->GetScreenSize() / PixelPerMat)
    {
        m_TileMap.LoadMapFile("field_00.tmx");

        m_Texture = SpriteTexture::Create(nullptr);
        m_Texture->SetRenderingProcess([this](IAppState *appState) { renderTileMap(appState); });
    }

    void FieldManager::renderTileMap(IAppState *appState)
    {
        const auto globalPos = m_Texture->GetParentalGlobalPosition().CopyBy<int>();

        const auto negativeCorrection = Vec2<int>{globalPos.X<0 ? -1 : 0, globalPos.Y<0 ? -1 : 0};

        const Vec2<int> startingChipPoint = (globalPos / PixelPerMat).CopyBy<int>() + negativeCorrection;

        const Vec2<int> matSize = m_TileMap.GetMatSize();

        const auto renderingChipStartingPoint = Vec2<int>{
            std::max(0, startingChipPoint.X),
            std::max(0, startingChipPoint.Y)};

        const auto renderingChipEndPoint = Vec2<int>{
                std::min(startingChipPoint.X + ScreenMatSize.X, matSize.X),
                std::min(startingChipPoint.Y + ScreenMatSize.Y, matSize.Y)};

        for (int chipY = renderingChipStartingPoint.Y; chipY<=renderingChipEndPoint.Y; ++chipY)
            for (int chipX = renderingChipStartingPoint.X; chipX<=renderingChipEndPoint.X; ++chipX)
            {
                const auto chipPos = Vec2{chipX, chipY};
                const Vec2<int> renderingScreenPos =
                        globalPos + Vec2{chipX, chipY} * PixelPerMat * appState->GetPixelPerUnit();
                const auto mapElement = m_TileMap.GetElementAt(chipPos);
                const auto chipList = mapElement->GetChipList();

                const auto srcSize = Vec2{PixelPerMat, PixelPerMat};
                const double pixelPerUnit = appState->GetPixelPerUnit();
                const auto pixelScaleSize = Vec2<double>{pixelPerUnit, pixelPerUnit};

                FieldRenderer renderer = FieldRenderer(
                        GameRoot::GetInstance().ResImage.get(),
                        chipPos,
                        renderingScreenPos,
                        appState->GetRenderer(),
                        srcSize,
                        pixelScaleSize,
                        &m_TileMap);

                for (const auto chip : chipList)
                    renderChip(chip, renderer, appState, renderingScreenPos);
            }
    }

    void FieldManager::renderChip(const field::TilePropertyChip *chip, field::FieldRenderer &renderer, IAppState *appState,
                                  const Vec2<int> &screenPos)
    {
        auto srcStarting = chip->SrcPoint;
        const auto srcSize = Vec2{PixelPerMat, PixelPerMat};
        const double pixelPerUnit = appState->GetPixelPerUnit();
        const auto pixelScaleSize = Vec2<double>{pixelPerUnit, pixelPerUnit};

        bool rendered = renderer.RenderChip(chip->Kind);
        if (!rendered)
            m_TileMap.GetTilesetImage().RenderGraph(
                    appState->GetRenderer(),
                    screenPos, Rect<int>(srcStarting, srcSize),
                    pixelScaleSize);
    }

    bool FieldManager::CanMoveTo(const MatPos &pos)
    {
        if (!m_TileMap.IsInRange(pos.GetVec())) return false;
        auto element = m_TileMap.GetElementAt(pos.GetVec());
        return !element->IsWall();
    }


}