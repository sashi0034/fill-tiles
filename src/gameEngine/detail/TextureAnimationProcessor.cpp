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
                                                         weak_ptr<TextureAnimationProcessor> *beforeAnimation)
            : m_TargetTexture(texture), m_ParentalPool(parentalPool)
    {
        if (beforeAnimation == nullptr)
            trigger();
        else if (auto beforeAnimationPtr = beforeAnimation->lock())
            m_BeforeAnimation = beforeAnimationPtr;
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
                                                                            weak_ptr<TextureAnimationProcessor> *beforeAnimation)
    {
        auto product = std::shared_ptr<TextureAnimationProcessor>(
                new TextureAnimationProcessor(texture, parentalPool, beforeAnimation));
        product->m_SelfWeakPtr = product;
        return product;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetLoop(int loop)
    {
        auto *animation = dynamic_cast<textureAnimation::EaseAbleAnimationBase *>(m_AnimationProcess.get());
        animation->GetEaser()->SetLoop(loop);
        return this;
    }


    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetEase(gameEngine::EAnimEase easeType)
    {
        auto* animation = dynamic_cast<textureAnimation::EaseAbleAnimationBase*>(m_AnimationProcess.get());
        animation->GetEaser()->SetEase(easeType);
        return this;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetRelative(bool isRelative)
    {
        auto* animation = dynamic_cast<textureAnimation::EaseAbleAnimationBase*>(m_AnimationProcess.get());
        animation->GetEaser()->SetRelative(isRelative);
        return this;
    }


    ITextureAnimationLinker *
    TextureAnimationProcessor::VirtualDelay(std::function<void()> process, double delayTime)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::VirtualDelay>(process, delayTime);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return static_cast<ITextureAnimationEaseProperty*>(nextAnimation.get());
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimPosition(Vec2<double> endPos, double duration)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        textureAnimation::AnimationBase* base = new textureAnimation::Position(m_TargetTexture, endPos, duration);
        nextAnimation->m_AnimationProcess = unique_ptr<textureAnimation::AnimationBase>(base);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimRotation(double endDeg, double duration)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Rotation>(
                m_TargetTexture, endDeg, duration);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimScale(const Vec2<double> &endScale, double duration)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Scale>(
                m_TargetTexture, endScale, duration);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    weak_ptr<ITextureAnimationPointer> TextureAnimationProcessor::GetWeakPtr()
    {
        return static_cast<const weak_ptr<ITextureAnimationEaseProperty> &>(m_SelfWeakPtr);
    }

    TextureAnimationProcessor::~TextureAnimationProcessor()
    = default;

    ITextureAnimationGraphProperty *TextureAnimationProcessor::AnimGraph(Vec2<int> cellSize)
    {
        auto nextAnimation = Create(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Graph>(
                m_TargetTexture, cellSize);

        m_ParentalPool->Register(nextAnimation);
        m_NextAnimation = nextAnimation;
        return nextAnimation.get();
    }

    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetCellSrcStart(Vec2<int> cellSrcStart)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetCellSrcStart(cellSrcStart);
        return this;
    }

    ITextureAnimationGraph *TextureAnimationProcessor::AddFrame(Vec2<int> cellPos, double duration)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->AddFrame(cellPos, duration, false);
        return this;
    }


    ITextureAnimationGraph *TextureAnimationProcessor::AddFrameFlipped(Vec2<int> cellPos, double duration)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->AddFrame(cellPos, duration, true);
        return this;
    }

    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetFrameLoop(int loop)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetLoopMax(loop);
        return this;
    }


    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetFrameLoopEndless(bool isEndless)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetLoopEndless(isEndless);
        return this;
    }

    void TextureAnimationProcessor::ForceDestroy()
    {
        m_ParentalPool->Destroy(this);
        if (auto beforeAnimation = m_BeforeAnimation.lock()) beforeAnimation->ForceDestroy();
    }

}


