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
    class ITextureAnimationGraphProperty;


    class ITextureAnimationStarter
    {
    public:
        virtual ITextureAnimationEaseProperty * AnimPosition(Vec2<double> endPos, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimRotation(double endDeg, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimScale(double endScale, double duration) = 0;
        virtual ITextureAnimationGraphProperty * AnimGraph(Vec2<int> cellSize) = 0;
        virtual ITextureAnimationLinker * VirtualDelay(std::function<void()> process, double deltaTime) = 0;
    };

    class ITextureAnimationPointer
    {
    public:
        virtual weak_ptr<ITextureAnimationPointer> GetWeakPtr() = 0;
        virtual void ForceDestroy() = 0;
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

    class ITextureAnimationGraph : public ITextureAnimationLinker
    {
    public:
        virtual ITextureAnimationGraph* AddFrame(Vec2<int> cellPos, double duration) = 0;
        virtual ITextureAnimationGraph* AddFrameFlipped(Vec2<int> cellPos, double duration) = 0;
    };

    class ITextureAnimationGraphProperty : public ITextureAnimationGraph
    {
    public:
        virtual ITextureAnimationGraphProperty* SetFrameLoop(int loop) = 0;
        virtual ITextureAnimationGraphProperty* SetFrameLoopEndless(bool loop) = 0;
        virtual ITextureAnimationGraphProperty* SetCellSrcStart(Vec2<int> cellSrcStart) = 0;
    };

    class TextureAnimationProcessor final:
            public ITextureAnimationStarter,
            public ITextureAnimationEaseProperty,
            public ITextureAnimationGraphProperty
    {
    public:
        static shared_ptr<TextureAnimationProcessor> Create(weak_ptr<SpriteTexture> &texture, IChildrenPool <TextureAnimationProcessor> *parentalPool, weak_ptr<TextureAnimationProcessor> *beforeAnimation);

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

        ITextureAnimationGraphProperty *AnimGraph(Vec2<int> cellSize) override;
        ITextureAnimationGraphProperty *SetCellSrcStart(Vec2<int> cellSrcStart) override;
        ITextureAnimationGraph *AddFrame(Vec2<int> cellPos, double duration) override;
        ITextureAnimationGraphProperty *SetFrameLoop(int loop) override;
        ITextureAnimationGraph *AddFrameFlipped(Vec2<int> cellPos, double duration) override;

        void Update(double deltaTime);
        void ForceDestroy() override;

        ~TextureAnimationProcessor();

        ITextureAnimationGraphProperty *SetFrameLoopEndless(bool isEndless) override;

    private:
        TextureAnimationProcessor(weak_ptr<SpriteTexture> &texture, IChildrenPool <TextureAnimationProcessor> *parentalPool, weak_ptr<TextureAnimationProcessor> *beforeAnimation);

        weak_ptr<TextureAnimationProcessor> m_SelfWeakPtr{};
        unique_ptr<textureAnimation::AnimationBase> m_AnimationProcess{};
        weak_ptr<SpriteTexture> m_TargetTexture;
        IChildrenPool <TextureAnimationProcessor> * m_ParentalPool;
        double m_CountTime = 0;

        bool m_IsImmediatelyStepToNext = false;
        bool m_IsTriggered = false;
        weak_ptr<TextureAnimationProcessor> m_BeforeAnimation{};
        weak_ptr<TextureAnimationProcessor> m_NextAnimation{};

        void trigger();
        void stepToNextAnimation();
    };
}


#endif //FILL_TILES_TEXTUREANIMATIONPROCESSOR_H
