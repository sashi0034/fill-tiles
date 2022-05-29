//
// Created by sashi0034 on 2022/05/29.
//

#include "textureAnimation.h"

namespace gameEngine::detail::textureAnimation
{

    VirtualDelay::VirtualDelay(std::function<void()> process, double delayTime)
            : m_DelayTime(delayTime), m_Process(process)
    {}

    bool VirtualDelay::UpdateAnimation(double deltaSecond)
    {
        if (m_Time>m_DelayTime) return false;

        m_Time += deltaSecond;
        if (m_Time>m_DelayTime){
           m_Process();
           return false;
        }

        return true;
    }

    TextureAnimationEaser * VirtualDelay::GetEaser()
    {
        return nullptr;
    }


    Position::Position(const weak_ptr<SpriteTexture> &targetTexture, const Vec2<double> &endPos, double endTime)
    : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        if (auto texture = targetTexture.lock())
        {
            m_StartPos = texture->GetPosition();
            m_EndPos = endPos;
        }
    }

    bool Position::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.lock())
            texture->SetPosition(m_Easer.CalcProgressValue<Vec2<double>>(m_StartPos, m_EndPos));
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser * Position::GetEaser()
    {
        return &m_Easer;
    }

    Rotation::Rotation(const weak_ptr<SpriteTexture> &targetTexture, double endDeg, double endTime)
            : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        if (auto texture = targetTexture.lock())
        {
            m_StartDeg = texture->GetRotationDeg();
            m_EndDeg = endDeg;
        }
    }

    bool Rotation::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.lock())
            texture->SetRotationDeg(m_Easer.CalcProgressValue<double>(m_StartDeg, m_EndDeg));
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser *Rotation::GetEaser()
    {
        return &m_Easer;
    }

    Scale::Scale(const weak_ptr<SpriteTexture> &targetTexture, double endScale, double endTime)
            : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        if (auto texture = targetTexture.lock())
        {
            m_StartScale = texture->GetScale();
            m_EndScale = endScale;
        }
    }

    bool Scale::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.lock())
            texture->SetScale(m_Easer.CalcProgressValue<double>(m_StartScale, m_EndScale));
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser *Scale::GetEaser()
    {
        return &m_Easer;
    }

    bool AnimationBase::UpdateAnimation(double)
    {
        assert(false);
        return false;
    }

    TextureAnimationEaser *AnimationBase::GetEaser()
    {
        assert(false);
        return nullptr;
    }

}
