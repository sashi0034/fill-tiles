//
// Created by sashi0034 on 2022/05/29.
//

#ifndef FILL_TILES_TEXTUREANIMATION_H
#define FILL_TILES_TEXTUREANIMATION_H

#include <functional>
#include "../TextureAnimator.h"
#include "TextureAnimationEaser.h"

namespace gameEngine::detail::textureAnimation
{
    class AnimationBase
    {
    public:
        virtual bool UpdateAnimation(double);   // returns false if object is dead.
        virtual ~AnimationBase() = default;
    };

    class EaseAbleAnimationBase : public AnimationBase
    {
    public:
        virtual TextureAnimationEaser * GetEaser() = 0;
        ~EaseAbleAnimationBase() override = default;
    };

    class VirtualDelay final: public AnimationBase
    {
    public:
        VirtualDelay(std::function<void()> process, double delayTime);
        bool UpdateAnimation(double deltaSecond) override;
        ~VirtualDelay() override = default;
    private:
        double m_Time=0;
        double m_DelayTime;
        std::function<void()> m_Process;
    };

    class Position final: public EaseAbleAnimationBase
    {
    public:
        Position(const weak_ptr<SpriteTexture> &targetTexture, const Vec2<double> &endPos, double endTime);
        bool UpdateAnimation(double deltaSecond) override;
        TextureAnimationEaser * GetEaser() override;
        ~Position() override = default;
    private:
        weak_ptr<SpriteTexture> m_Texture;
        Vec2<double> m_StartPos{};
        Vec2<double> m_EndPos{};
        TextureAnimationEaser m_Easer;
    };

    class Rotation final: public EaseAbleAnimationBase
    {
    public:
        Rotation(const weak_ptr<SpriteTexture> &targetTexture, double endDeg, double endTime);
        bool UpdateAnimation(double deltaSecond) override;
        TextureAnimationEaser * GetEaser() override;
        ~Rotation() override = default;
    private:
        weak_ptr<SpriteTexture> m_Texture;
        double m_StartDeg=0;
        double m_EndDeg{};
        TextureAnimationEaser m_Easer;
    };

    class Scale final: public EaseAbleAnimationBase
    {
    public:
        Scale(const weak_ptr<SpriteTexture> &targetTexture, double endScale, double endTime);
        bool UpdateAnimation(double deltaSecond) override;
        TextureAnimationEaser * GetEaser() override;
        ~Scale() override = default;
    private:
        weak_ptr<SpriteTexture> m_Texture;
        double m_StartScale = 0;
        double m_EndScale{};
        TextureAnimationEaser m_Easer;
    };

    class Graph final: public AnimationBase
    {
    public:
        Graph(const weak_ptr<SpriteTexture> &targetTexture, Vec2<int> cellSize);
        bool UpdateAnimation(double deltaSecond) override;
        void AddFrame(Vec2<int> &cellPos, double duration, bool isFlip);
        void SetLoopMax(int loopMax);
        void SetLoopEndless(bool isEndless);
        void SetCellSrcStart(const Vec2<int> &cellSrcStart);
        ~Graph() override = default;

    private:
        void updateTexture();
        void stepToNextFrame();
        void stepToNextLoop();

        struct FrameElement
        {
            const Vec2<int> CellPos;
            const double Duration;
            const bool IsFlip;
        };
        std::vector<FrameElement> m_FrameList{};
        weak_ptr<SpriteTexture> m_Texture;
        Vec2<int> m_CellSize{};
        Vec2<int> m_CellSrcStart{};
        double m_CurrentFrameTime = 0;
        int m_CurrentFrameIndex = 0;
        int m_LoopMax = 0;
        int m_LoopCount = 0;
        bool m_IsLoopEndless = false;
    };

}


#endif //FILL_TILES_TEXTUREANIMATION_H
