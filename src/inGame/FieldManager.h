//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_FIELDMANAGER_H
#define FILL_TILES_FIELDMANAGER_H

#include "ActorBase.h"
#include "field/TileMap.h"
#include "field/TileMapMatElement.h"
#include "resource/Image.h"

namespace inGame
{
    class FieldManager : ActorBase
    {
    public:
        explicit FieldManager(IChildrenPool<ActorBase> *parentPool, IAppState *app);

        static inline const int PixelPerChip = 16;
        const Vec2<int> ScreenChipSize;
    private:
        void renderTileMap(IAppState *appState);
        void renderChip(const Vec2<int> &matPos, const Vec2<int> &screenPos, IAppState *appState,
                        const field::TilePropertyChip *chip);



        field::TileMap m_TileMap{};
        shared_ptr<SpriteTexture> m_Texture;

        static void renderPlateauCliff(const Vec2<int> &matPos, const Vec2<int> &screenPos, const IAppState *appState,
                                Graph *image, const Vec2<int> &srcSize, const Vec2<double> &pixelScaleSize,
                                const std::function<bool(int, int)>& isNeighbor);
    };
}


#endif //FILL_TILES_FIELDMANAGER_H
