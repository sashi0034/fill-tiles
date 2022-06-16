//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_FIELDMANAGER_H
#define FILL_TILES_FIELDMANAGER_H

#include "ActorBase.h"
#include "field/TileMap.h"
#include "field/TileMapMatElement.h"
#include "resource/Image.h"
#include "field/FieldRenderer.h"
#include "MatPos.h"

namespace inGame
{
    class FieldManager : ActorBase
    {
    public:
        explicit FieldManager(IChildrenPool<ActorBase> *parentPool, IAppState *app);

        bool CanMoveTo(const MatPos& pos);

        static inline const int PixelPerMat = 16;
        static inline const Vec2<int> MatPixelSize = {PixelPerMat, PixelPerMat};
        static inline const Vec2<double> CharacterPadding{0, -PixelPerMat / 4.0};
        const Vec2<int> ScreenMatSize;
    private:
        void renderTileMap(IAppState *appState);
        void renderChip(const field::TilePropertyChip *chip, field::FieldRenderer &renderer, IAppState *appState,
                        const Vec2<int> &screenPos);
        field::TileMap m_TileMap{};
        shared_ptr<SpriteTexture> m_Texture;

    };
}


#endif //FILL_TILES_FIELDMANAGER_H
