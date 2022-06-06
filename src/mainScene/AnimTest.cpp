//
// Created by sashi0034 on 2022/05/28.
//

#include "AnimTest.h"
#include "MainRoot.h"

namespace mainScene
{
    AnimTest::AnimTest(IChildrenPool<ChildBase> *belonging)
            : ChildBase(belonging),
              m_Action(coroutine<CoroTask>::pull_type{std::bind(wait, std::placeholders::_1, this)})
    {
        m_Image = MainRoot::GetInstance().ResImage->dango_wolf_24x24.get();

        m_Spr = Sprite::Create();
        m_Texture = SpriteTexture::Create(m_Spr, m_Image);
        m_Spr->SetTexture(m_Texture);
        m_Texture->SetSrcRect(Rect<int>{0,0,24, 24});

        std::cout << "#1" << std::endl;
    }

    CoroTask AnimTest::wait(coroutine<CoroTask>::push_type &yield, AnimTest *self)
    {
        yield(CoroTask::RespondPending());

        auto& mainRoot = MainRoot::GetInstance();
        auto appState = mainRoot.AppStatePtr;
        auto screenSize = appState->GetScreenSize().EachTo<double>();
        self->m_Pos = screenSize/2.0;
        self->m_Texture->SetPosition(self->m_Pos);

        /* example */
//        mainRoot.GetTextureAnimator().TargetTo(self->m_Texture)
//                ->AnimGraph(Vec2<int>{24, 24})->SetFrameLoop(10)->FromSrc(Vec2<int>{0, 0})
//                ->AddFrame(Vec2<int>{0, 0}, 0.2)
//                ->AddFrame(Vec2<int>{1, 0}, 0.2)
//                ->AddFrame(Vec2<int>{2, 0}, 0.2)
//                ->AddFrame(Vec2<int>{3, 0}, 0.2);


        mainRoot.GetTextureAnimator().TargetTo(self->m_Texture)
                ->AnimPosition(Vec2<double>{64, 64}, 3.0)->SetEase(EAnimEase::Linear)->SetLoop(2)->SetRelative(false)
                ->With()
                ->AnimRotation(60, 3.0)->SetEase(EAnimEase::Linear)->SetLoop(2)
                ->Then()
                ->AnimPosition(Vec2<double>{32, 32}, 3.0)->SetEase(EAnimEase::Linear)->SetLoop(2)->SetRelative(true)
                ->Then()
                ->VirtualDelay([]() { std::cout << "finished animation?" << std::endl; }, 1.0)
                ->Then()
                ->VirtualDelay([]() { std::cout << "yes!" << std::endl; }, 0)
                ->Then()
                ->VirtualDelay([]() { std::cout << "finished animation!" << std::endl; }, 0.5);


        yield(CoroTask::RespondPending());
//
//        for (int i=0; i<256; ++i)
//        {
//            self->m_Pos = self->m_Pos + Vec2<double>{128.0-i, 128.0-i} * appState->GetTime().GetDeltaSec();
//            yield(CoroTask::RespondPending());
//
//        }
//        self->m_Texture->SetRotationDeg(45);

        return CoroTask::RespondSuccess();
    }

    void AnimTest::Update()
    {
        if (m_Action) m_Action();
        m_Texture->SetPosition(m_Pos);
    }
}
