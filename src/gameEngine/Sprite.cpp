//
// Created by sashi0034 on 2022/05/07.
//

#include "Sprite.h"

#include <memory>

namespace gameEngine
{
    std::vector<weak_ptr<Sprite>> Sprite::spritePool = {};

    Sprite::Sprite()
    {
        m_UpdateProcess = [](IAppState*){};
    }

    shared_ptr<Sprite> Sprite::Create()
    {
        auto product = shared_ptr<Sprite>(new Sprite());

        product->m_SelfPointer = product;
        spritePool.push_back(product);

        return product;
    }

    void Sprite::SetTexture(shared_ptr<SpriteTexture> texture)
    {
        m_Texture = std::move(texture);
    }

    const shared_ptr<SpriteTexture> &Sprite::GetTexture() const
    {
        return m_Texture;
    }

    void Sprite::SetUpdateProcess(const std::function<void(IAppState*)> &process)
    {
        m_UpdateProcess = process;
    }

    void Sprite::UpdateAll(IAppState* appState)
    {
        int size = spritePool.size();
        std::vector<int> garbageIndexes{};

        for (int i = 0; i < size; ++i)
            if (auto updatingSpr = spritePool[i].lock())
                updatingSpr->m_UpdateProcess(appState);
            else
                garbageIndexes.push_back(i);

        collectGarbageInSpritePool(garbageIndexes);
    }

    void Sprite::collectGarbageInSpritePool(std::vector<int> &garbageIndexes)
    {
        for (int i=garbageIndexes.size()-1; i>=0; --i)
        {
            int index = garbageIndexes[i];
            spritePool.erase(spritePool.begin()+index);
        }
    }


}
