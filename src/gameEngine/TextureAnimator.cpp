//
// Created by sashi0034 on 2022/05/28.
//

#include "TextureAnimator.h"

namespace gameEngine{
    detail::ITextureAnimationStarter* TextureAnimator::TargetTo(shared_ptr<SpriteTexture> &texture)
    {
        weak_ptr<SpriteTexture> texturePtr = texture;
        auto product = detail::TextureAnimationProcessor::Create(texturePtr, &m_Pool, nullptr);
        m_Pool.Register(product);
        return product.get();
    }

    void TextureAnimator::Update(double deltaTime)
    {
        m_Pool.ProcessEach([&deltaTime](shared_ptr<detail::TextureAnimationProcessor>& animation){ animation->Update(deltaTime);});
    }

    TextureAnimator::~TextureAnimator()
    {
        m_Pool.Release();
    }


}