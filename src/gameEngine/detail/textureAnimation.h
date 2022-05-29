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
        virtual TextureAnimationEaser * GetEaser();
        virtual ~AnimationBase() = default;
    };

    class VirtualDelay final: public AnimationBase
    {
    public:
        VirtualDelay(std::function<void()> process, double delayTime);
        bool UpdateAnimation(double deltaSecond) override;
        TextureAnimationEaser * GetEaser() override;
        ~VirtualDelay() override = default;
    private:
        double m_Time=0;
        double m_DelayTime;
        std::function<void()> m_Process;
    };

    class Position final: public AnimationBase
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

    class Rotation final: public AnimationBase
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

    class Scale final: public AnimationBase
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

}


#endif //FILL_TILES_TEXTUREANIMATION_H
