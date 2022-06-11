//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_SPRITE_H
#define FILL_TILES_SPRITE_H

#include <memory>
#include "Vec2.h"
#include "SpriteTexture.h"

using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

#if 0
namespace gameEngine
{
    class SpriteTexture;

    class Sprite
    {
        static std::vector<weak_ptr<Sprite>> spriteTexturePool;

        weak_ptr<Sprite> m_SelfPointer;
        shared_ptr<SpriteTexture> m_Texture{};
        std::function<void(IAppState*)> m_UpdateProcess;
        static void collectGarbageInSpritePool(std::vector<int>& garbageIndexes);

        Sprite();
    public:
        static shared_ptr<Sprite> Create();

        void SetTexture(shared_ptr<SpriteTexture> texture);
        const shared_ptr<SpriteTexture>& GetTexture() const;

        void SetUpdateProcess(const std::function<void(IAppState*)>& process);

        static void UpdateAll(IAppState* appState);

    };
}
#endif

#endif //FILL_TILES_SPRITE_H
