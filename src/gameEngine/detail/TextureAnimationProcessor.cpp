//
// Created by sashi0034 on 2022/05/28.
//

#include "TextureAnimationProcessor.h"

#include <memory>
#include "textureAnimation.h"

namespace gameEngine::detail
{
    TextureAnimationProcessor::TextureAnimationProcessor(weak_ptr<SpriteTexture> &texture,
                                                         IChildrenPool<TextureAnimationProcessor> *parentalPool,
                                                         bool isFirst)
            : m_TargetTexture(texture), m_ParentalPool(parentalPool)
    {
        if (isFirst) trigger();
    }


    void TextureAnimationProcessor::Update(double deltaTime)
    {
        if (!m_IsTriggered) return;

        bool isRunning = false;

        if (m_AnimationProcess != nullptr)
            isRunning = m_AnimationProcess->UpdateAnimation(deltaTime);

        if (!isRunning) stepToNextAnimation();
    }

    void TextureAnimationProcessor::stepToNextAnimation()
    {
        if (auto next = m_NextAnimation.lock())
            next->trigger();

        auto isDestroyed = m_ParentalPool->Destroy(this);
        assert(isDestroyed);
    }

    ITextureAnimationStarter *TextureAnimationProcessor::Then()
    {
        return this;
    }

    ITextureAnimationStarter *TextureAnimationProcessor::With()
    {
        m_IsImmediatelyStepToNext = true;
        return this;
    }

    void TextureAnimationProcessor::trigger()
    {
        m_IsTriggered = true;
        if (m_IsImmediatelyStepToNext)
            if (auto next = m_NextAnimation.lock())
                next->trigger();
    }


    shared_ptr<TextureAnimationProcessor> TextureAnimationProcessor::Create(weak_ptr<SpriteTexture> &texture,
                                                                            IChildrenPool<TextureAnimationProcessor> *parentalPool,
                                                                            bool isFirst)
    {
        auto product = std::shared_ptr<TextureAnimationProcessor>(
                new TextureAnimationProcessor(texture, parentalPool, isFirst));
        product->m_SelfPtr = product;
        return product;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetLoop(int loop)
    {
        m_AnimationProcess->GetEaser()->SetLoop(loop);
        return this;
    }


    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetEase(gameEngine::EAnimEase easeType)
    {
        m_AnimationProcess->GetEaser()->SetEase(easeType);
        return this;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetRelative(bool isRelative)
    {
        m_AnimationProcess->GetEaser()->SetRelative(isRelative);
        return this;
    }


    ITextureAnimationLinker *
    TextureAnimationProcessor::VirtualDelay(std::function<void()> process, double delayTime)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, false);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::VirtualDelay>(process, delayTime);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimPosition(Vec2<double> endPos, double duration)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, false);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Position>(
                m_TargetTexture, endPos, duration);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimRotation(double endDeg, double duration)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, false);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Rotation>(
                m_TargetTexture, endDeg, duration);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimScale(double endScale, double duration)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, false);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Scale>(
                m_TargetTexture, endScale, duration);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    weak_ptr<ITextureAnimationPointer> TextureAnimationProcessor::GetWeakPtr()
    {
        return m_SelfPtr;
    }

    TextureAnimationProcessor::~TextureAnimationProcessor()
    {}

}

