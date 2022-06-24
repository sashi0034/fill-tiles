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

    FieldManager::FieldManager(IChildrenPool<ActorBase> *belonging, IMainScene *parentalScene) :
            ActorBase(belonging),
            ScreenMatSize(GameRoot::GetInstance().GetAppState()->GetScreenSize() / PixelPerMat),
            m_ParentalScene(parentalScene), m_TileMap(parentalScene)
    {
        m_Texture.SetRenderingProcess([this](IAppState *appState) { renderTileMap(appState); });
        ZIndexBackGround(&m_Texture).ApplyZ();

        m_ParentalScene->GetScrollManager()->RegisterSprite(m_Texture);
    }

    void FieldManager::Init()
    {
        m_TileMap.LoadMapFile("field_00.tmx");
    }


    void FieldManager::renderTileMap(IAppState *appState)
    {
        const auto globalPos = m_Texture.GetParentalGlobalPosition();
        const auto screenGlobalPos = (globalPos * appState->GetPixelPerUnit()).CastTo<int>();

        const auto negativeCorrection = Vec2<int>{globalPos.X<0 ? -1 : 0, globalPos.Y<0 ? -1 : 0};

        const Vec2<int> startingChipPoint = (globalPos * -1 / PixelPerMat).CastTo<int>() + negativeCorrection;

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

                // @todo: テクスチャをバッファに格納して処理を減らす
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

    bool FieldManager::CanMoveTo(const MatPos &currMatPos, EAngle goingAngle)
    {
        const auto diffVec = Angle(goingAngle).ToXY();
        const auto currPos = currMatPos.GetVec();
        const auto nextPos = currPos + diffVec;
        if (!m_TileMap.IsInRange(nextPos)) return false;

        const auto currPosEle = m_TileMap.GetElementAt(currPos);
        const auto nextPosEle = m_TileMap.GetElementAt(nextPos);

        bool result =
                !currPosEle->GetCliffFlag(goingAngle) &&
                !nextPosEle->IsWall() &&
                !m_DynamicCharacterCollider.IsHitWith((nextPos * PixelPerMat + MatPixelSize / 2).CastTo<double>());

        return result;
    }

    IChildrenPool<character::CharacterBase> *FieldManager::GetCharacterPool()
    {
        return &m_ChildrenPool;
    }

    ITextureAnimator* FieldManager::GetCharacterAnimator()
    {
        return &m_CharacterAnimator;
    }

    void FieldManager::Update(IAppState* app)
    {
        m_CharacterAnimator.Update(app->GetTime().GetDeltaSec());
    }

    TextureColliderManager *FieldManager::GetCharacterCollider()
    {
        return &m_DynamicCharacterCollider;
    }

    void FieldManager::OverwriteWallFlag(const MatPos &pos, const Vec2<int> &fillSize, bool isWall)
    {
        Vec2<int> startPos = pos.GetVec();
        Vec2<int> nonNegativeSize = fillSize;

        if (nonNegativeSize.X < 0)
        {
            nonNegativeSize.X *= -1;
            startPos.X = startPos.X - nonNegativeSize.X + 1;
        }
        if (nonNegativeSize.Y < 0)
        {
            nonNegativeSize.Y *= -1;
            startPos.Y = startPos.Y - nonNegativeSize.Y + 1;
        }

        for (int x=0; x < nonNegativeSize.X; ++x)
            for (int y=0; y<nonNegativeSize.Y; ++y)
            {
                auto targetPos = startPos + Vec2<int>{x, y};
                if (m_TileMap.IsInRange(targetPos))
                    m_TileMap.GetElementAt(targetPos)->OverwriteIsWall(isWall);
            }
    }

    void FieldManager::OverwriteWallFlag(const MatPos &pos, bool isWall)
    {
        OverwriteWallFlag(pos, Vec2<int>{1, 1}, isWall);
    }

    field::ITileMap* FieldManager::GetTileMap()
    {
        return &m_TileMap;
    }

    FieldManager::~FieldManager()
    {
        m_ChildrenPool.Release();
    }


}