//
// Created by sashi0034 on 2022/05/28.
//

#include "TextureAnimator.h"

namespace gameEngine{
    detail::ITextureAnimationStarter* TextureAnimator::TargetTo(SpriteTexture &texture)
    {
        auto product = new detail::TextureAnimationProcessor(texture.GetWeakPtr(), &m_Pool, nullptr);
        m_Pool.Birth(product);
        return product;
    }

    void TextureAnimator::Update(double deltaTime)
    {
        m_Pool.ProcessEach([&deltaTime](detail::TextureAnimationProcessor& animation){ animation.Update(deltaTime);});
    }

    TextureAnimator::~TextureAnimator()
    {
        m_Pool.Release();
    }

    void TextureAnimator::Release()
    {
        m_Pool.Release();
    }

    bool TextureAnimator::Destroy(TextureAnimationWeakPtr &target)
    {
        if (auto targetPtr = target.GetPtr())
        {
            return m_Pool.Destroy(dynamic_cast<detail::TextureAnimationProcessor*>(targetPtr));
        }
        return false;
    }


}