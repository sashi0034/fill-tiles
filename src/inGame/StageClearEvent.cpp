//
// Created by sashi0034 on 2022/09/20.
//

#include "StageClearEvent.h"

namespace inGame
{
    GameRoot *StageClearEventArgs::GetRoot() const
    {
        return SceneRef->GetRoot();
    }

    TextureAnimator *StageClearEventArgs::GetAnimator() const
    {
        return SceneRef->GetEffectManager()->GetAnimator();
    }

    CoroutineManager *StageClearEventArgs::GetCoroutineManager() const
    {
        return SceneRef->GetEffectManager()->GetCoroutineManager();
    }

    void StageClearEvent::Start(const StageClearEventArgs &args)
    {
        args.GetCoroutineManager()->Start([&args](auto&& yield){ StageClearEvent::startEvent(yield, args);});
    }

    void StageClearEvent::startEvent(CoroTaskYield &yield, StageClearEventArgs args)
    {
        yield();

        auto const labelClearImage = args.GetRoot()->RscImage->clear_label.get();
        SpriteTexture labelClear = SpriteTexture::Create(
                labelClearImage, Rect<int>{Vec2{0, 0}, labelClearImage->GetSize()});
        labelClear.SetRenderingProcess(renderingProcess::WrapRenderSpriteDotByDot(&labelClear));
        labelClear.SetPositionParent(args.GetRoot()->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Middle));
        labelClear.SetPosition(Vec2<double>{-labelClearImage->GetSize().X / 2.0, -labelClearImage->GetSize().Y / 1.0} /
                               pixel::PixelPerUnit);

        while (true)
        {
            yield();
        }
    }
} // inGame