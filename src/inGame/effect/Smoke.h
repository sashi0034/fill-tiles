//
// Created by sashi0034 on 2022/07/05.
//

#ifndef FILL_TILES_SMOKE_H
#define FILL_TILES_SMOKE_H

#include "../MainScene.h"
#include "../EffectManager.h"

namespace inGame::effect
{
    class Smoke final : public ActorBase
    {
    public:
        static void Produce(EffectManager *effectManager, const Vec2<double> &pos);

        void Update(IAppState *appState) override;
    private:
        double m_TimeCount;
        Vec2<double> m_Vel;

        Smoke(EffectManager *effectManager, const Vec2<double> &pos, const Vec2<double> &velocity,
              double rotationDeg);
        EffectManager* m_Manager;
        SpriteTexture m_Texture = SpriteTexture::Create();
        static CoroTask produceWithRotating(CoroTaskYield& yield, EffectManager *manager, const Vec2<double> &pos);
    };
}


#endif //FILL_TILES_SMOKE_H
