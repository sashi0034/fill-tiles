//
// Created by sashi0034 on 2022/07/05.
//

#include "Smoke.h"

namespace inGame::effect
{

    Smoke::Smoke(EffectManager *effectManager, const Vec2<double> &pos, const Vec2<double> &velocity,
                 double rotationDeg)
    : ActorBase(effectManager->GetChildren()), m_Vel(velocity), m_Manager(effectManager)
    {
        m_Texture.SetGraph(effectManager->GetRoot()->ResImage->smoke_48x32.get());
        //m_Texture.SetRenderingProcess(std::bind(renderingProcess::RenderSpriteTwoDots, std::placeholders::_1, &m_Texture));
        m_Texture.SetSrcRect(Rect<int>{0, 0, 48, 32});
        m_Texture.SetRotationDeg(rotationDeg);
        m_Texture.SetBlend(GraphBlend(160));

        util::SetTextureCentral(m_Texture, pos);

//        m_Texture.SetScale(Vec2{0.0, 0.0});
//        effectManager->GetAnimator()->TargetTo(m_Texture.GetWeakPtr())
//            ->AnimScale(Vec2{1.0, 1.0}, 1.0)->SetEase(EAnimEase::OutBack)
//            ->Then()
//            ->AnimScale(Vec2{.0, .0}, 1.0)->SetEase(EAnimEase::Linear);
    }

    void Smoke::Produce(EffectManager *effectManager, const Vec2<double> &pos)
    {

        effectManager->GetCoroutineManager()->Start(
                new CoroTaskCall(std::bind(produceWithRotating, std::placeholders::_1, effectManager, pos)));
    }

    CoroTask Smoke::produceWithRotating(CoroTaskYield &yield, EffectManager *manager, const Vec2<double> &pos)
    {
        constexpr int numGenerate = 6;
        constexpr int numCircuit = 2;
        constexpr double duration = 0.05;

        for (int i=0; i<numGenerate * numCircuit + 1; ++i)
        {
            const int deg = i * ((360.0-360.0/(numGenerate*numCircuit)) / numGenerate);
            const double rad = deg / 180.0 * M_PI;
            constexpr double radius = 4;
            constexpr double velSize = 20;
            const Vec2<double> deltaPos = Vec2{std::cos(rad), std::sin(rad)} * radius;
            const Vec2<double> vel = Vec2{std::cos(rad), std::sin(rad)} * velSize;
            manager->GetChildren()->Birth(new Smoke(manager, pos + deltaPos, vel, 90 + deg));

            coroUtil::WaitForTime(yield, duration);
        }
    }

    void Smoke::Update(IAppState *appState)
    {
        constexpr double scaleSpeed = 5;
        const double scale = 0.7 - 0.3 * std::cos(m_TimeCount * scaleSpeed * M_PI);

        m_Texture.SetScale(Vec2{scale, scale});
        m_Texture.SetPosition(m_Texture.GetPosition() + m_Vel * appState->GetTime().GetDeltaSec());

        m_TimeCount += appState->GetTime().GetDeltaSec();
        constexpr double lifeTime = 3.0;
        if (m_TimeCount>lifeTime)
        {
            m_Manager->GetChildren()->Destroy(this);
            return;
        }
    }
}