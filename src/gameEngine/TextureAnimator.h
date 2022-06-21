//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_TEXTUREANIMATOR_H
#define FILL_TILES_TEXTUREANIMATOR_H

#include "SpriteTexture.h"
#include "ChildrenPool.h"
#include "boost/coroutine2/coroutine.hpp"
#include "detail/TextureAnimationProcessor.h"

namespace gameEngine
{
    namespace detail
    {
        class ITextureAnimationStarter;
    }

    enum class EAnimEase{
        Linear,
        InBack,
        OutBack,
    };

    class ITextureAnimator
    {
    public:
        virtual detail::ITextureAnimationStarter * TargetTo(const WeakPtr <SpriteTexture> &texture) = 0;
    };

    class TextureAnimator : public ITextureAnimator
    {
    public:
        detail::ITextureAnimationStarter * TargetTo(const WeakPtr <SpriteTexture> &texture) override;
        //unique_ptr<TextureAnimationCreator> VirtualTo();

        void Update(double deltaTime);
        void Release();
        ~TextureAnimator();
    private:
        ChildrenPool<detail::TextureAnimationProcessor> m_Pool;
    };


}


#endif //FILL_TILES_TEXTUREANIMATOR_H
