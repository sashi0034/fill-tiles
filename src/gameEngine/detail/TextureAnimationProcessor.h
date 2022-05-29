//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_TEXTUREANIMATIONPROCESSOR_H
#define FILL_TILES_TEXTUREANIMATIONPROCESSOR_H

#include "../SpriteTexture.h"
#include "../ChildrenPool.h"

namespace gameEngine{
    enum class EAnimEase;
    class TextureAnimator;

}
namespace gameEngine::detail
{
    namespace textureAnimation
    {
        class AnimationBase;
    }
    class ITextureAnimationEaseProperty;
    class ITextureAnimationLinker;


    class ITextureAnimationStarter
    {
    public:
        virtual ITextureAnimationEaseProperty * AnimPosition(Vec2<double> endPos, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimRotation(double endDeg, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimScale(double endScale, double duration) = 0;
        virtual ITextureAnimationLinker * VirtualDelay(std::function<void()> process, double deltaTime) = 0;
    };

    class ITextureAnimationPointer
    {
    public:
        virtual weak_ptr<ITextureAnimationPointer> GetWeakPtr() = 0;
    };

    class ITextureAnimationWith : public ITextureAnimationPointer
    {
    public:
        virtual ITextureAnimationStarter * With() = 0;
    };

    class ITextureAnimationLinker : public ITextureAnimationWith
    {
    public:
        virtual ITextureAnimationStarter * Then() = 0;
    };

    class ITextureAnimationEaseProperty : public ITextureAnimationLinker
    {
    public:
        virtual ITextureAnimationEaseProperty * SetEase(gameEngine::EAnimEase easeType) = 0;
        virtual ITextureAnimationEaseProperty * SetLoop(int loop) = 0;
        virtual ITextureAnimationEaseProperty * SetRelative(bool isRelative) = 0;
    };

    class TextureAnimationProcessor final: public ITextureAnimationStarter, public ITextureAnimationEaseProperty
    {
    public:
        static shared_ptr<TextureAnimationProcessor> Create(weak_ptr<SpriteTexture> &texture, IChildrenPool <TextureAnimationProcessor> *parentalPool, bool isFirst);

        ITextureAnimationEaseProperty * AnimPosition(Vec2<double> endPos, double duration) override;
        ITextureAnimationEaseProperty * AnimRotation(double endDeg, double duration) override;
        ITextureAnimationEaseProperty * AnimScale(double endScale, double duration) override;
        ITextureAnimationLinker * VirtualDelay(std::function<void()> process, double delayTime) override;
        ITextureAnimationStarter * Then() override;
        ITextureAnimationStarter * With() override;
        ITextureAnimationEaseProperty * SetEase(gameEngine::EAnimEase easeType) override;
        ITextureAnimationEaseProperty * SetLoop(int loop) override;
        ITextureAnimationEaseProperty * SetRelative(bool isRelative) override;
        weak_ptr<ITextureAnimationPointer> GetWeakPtr() override;
        void Update(double deltaTime);

        ~TextureAnimationProcessor();
    private:
        TextureAnimationProcessor(weak_ptr<SpriteTexture> &texture, IChildrenPool <TextureAnimationProcessor> *parentalPool, bool isFirst);

        weak_ptr<TextureAnimationProcessor> m_SelfPtr{};
        unique_ptr<textureAnimation::AnimationBase> m_AnimationProcess{};
        weak_ptr<SpriteTexture> m_TargetTexture;
        IChildrenPool <TextureAnimationProcessor> * m_ParentalPool;
        double m_CountTime = 0;

        bool m_IsImmediatelyStepToNext = false;
        bool m_IsTriggered = false;
        weak_ptr<TextureAnimationProcessor> m_NextAnimation{};

        void trigger();
        void stepToNextAnimation();
    };
}


#endif //FILL_TILES_TEXTUREANIMATIONPROCESSOR_H
