//
// Created by sashi0034 on 2022/06/11.
//

#include "FieldManager.h"
#include "GameRoot.h"
#include "field/FieldRenderer.h"
#include "MainScene.h"
#include "ZIndex.h"

namespace inGame
{
    using namespace field;

    FieldManager::FieldManager(IMainScene *parentalScene) :
            ScreenMatSize(GameRoot::GetInstance().GetAppState()->GetScreenSize() / PixelPerMat),
            m_ParentalScene(parentalScene), m_TileMap(parentalScene)
    {
        m_Texture = SpriteTexture::Create(nullptr);
        m_Texture->SetRenderingProcess([this](IAppState *appState) { renderTileMap(appState); });
        m_Texture->SetZ(ZIndexBackGround().GetZ());

        m_ParentalScene->GetScrollManager()->RegisterSprite(m_Texture);
    }

    void FieldManager::Init()
    {
        m_TileMap.LoadMapFile("field_00.tmx");
    }


    void FieldManager::renderTileMap(IAppState *appState)
    {
        const auto globalPos = m_Texture->GetParentalGlobalPosition();
        const auto screenGlobalPos = (globalPos * appState->GetPixelPerUnit()).CopyBy<int>();

        const auto negativeCorrection = Vec2<int>{globalPos.X<0 ? -1 : 0, globalPos.Y<0 ? -1 : 0};

        const Vec2<int> startingChipPoint = (globalPos * -1 / PixelPerMat).CopyBy<int>() + negativeCorrection;

        const Vec2<int> matSize = m_TileMap.GetMatSize();

        const auto renderingChipStartingPoint = Vec2<int>{
            std::max(0, startingChipPoint.X),
            std::max(0, startingChipPoint.Y)};

        const auto renderingChipEndPoint = Vec2<int>{
                std::min(startingChipPoint.X + 1 + ScreenMatSize.X, matSize.X-1),
                std::min(startingChipPoint.Y + 1 + ScreenMatSize.Y, matSize.Y-1)};


        for (int chipY = renderingChipStartingPoint.Y; chipY<=renderingChipEndPoint.Y; ++chipY)
            for (int chipX = renderingChipStartingPoint.X; chipX<=renderingChipEndPoint.X; ++chipX)
            {
                const auto chipPos = Vec2{chipX, chipY};
                const Vec2<int> renderingScreenPos =
                        screenGlobalPos + (Vec2<int>{chipX, chipY} * PixelPerMat) * appState->GetPixelPerUnit();
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

    IChildrenPool<character::CharacterBase> *FieldManager::GetCharacterPool()
    {
        return &m_ChildrenPool;
    }



}