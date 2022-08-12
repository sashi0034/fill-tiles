//
// Created by sashi0034 on 2022/08/12.
//

#include "TextureScrapping.h"

namespace inGame::effect
{
    void TextureScrapping::Produce(const TextureScrappingArgs &args)
    {
        args.EffectManagerRef->GetCoroutineManager()->Start([&](auto&& yield){ produceEffectAsync(yield, args);});
    }

    void TextureScrapping::produceEffectAsync(CoroTaskYield &yield, TextureScrappingArgs args)
    {
        yield();

        auto const currPos = args.Pos;
        auto const srcRect = args.SrcRect;
        auto const srcGraph = args.SrcGraph;

        constexpr int stepSize = 8;

        auto const posForAngle = currPos + Vec2<double>(srcRect.Width/2, srcRect.Height+srcRect.Height/2) - Vec2<double>{stepSize/2.0, stepSize/2.0};

        for (int x=0; x<srcRect.Width; x+=stepSize)
        {
            for (int y=0; y<srcRect.Height; y+= stepSize)
            {
                const Rect<int> stripRect = Rect<int>{x, y, stepSize, stepSize};
                const Vec2<double> stripPos = currPos + Vec2<double>{(double)x , (double)y};
                const double velTheta = std::atan2(stripPos.Y-posForAngle.Y, stripPos.X - posForAngle.X);
                const Vec2<double> normalizedVel{std::cos(velTheta), std::sin(velTheta)};
                constexpr double velSize = 10;

                args.EffectManagerRef->GetChildren()->Birth(new TextureScrapping(
                        args.EffectManagerRef, srcGraph, stripRect,
                        stripPos, normalizedVel * velSize));
            }
        }
    }

    TextureScrapping::TextureScrapping(EffectManager *effectManager, Graph *const srcGraph, const Rect<int> &srcRect,
                                       const Vec2<double> &pos, const Vec2<double> &velocity)
                                       : ActorBase(effectManager->GetChildren()),
                                       m_Manager(effectManager),
                                       m_Pos(pos),
                                       m_Vel(velocity)
    {
        m_Texture.SetGraph(srcGraph);
        m_Texture.SetSrcRect(srcRect);
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetPosition(pos);
    }

    void TextureScrapping::Update(IAppState *appState)
    {
        m_Lifetime += appState->GetTime().GetDeltaSec();
        constexpr double maxLifetime = 3.0;
        if (m_Lifetime > maxLifetime) {
            getBelongingPool()->Destroy(this);
            return;
        }

        constexpr double gravity = 10.0;
        m_Vel = m_Vel + Vec2{0.0, gravity} * appState->GetTime().GetDeltaSec();

        m_Pos = m_Pos + m_Vel * appState->GetTime().GetDeltaSec();
        m_Texture.SetPosition(m_Pos);
    }
} // inGame