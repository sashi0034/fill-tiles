//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_TALKINGBALLOON_H
#define FILL_TILES_TALKINGBALLOON_H

#include "SDL_ttf.h"
#include "ActorBase.h"
#include "GameRoot.h"
#include "MainScene.h"
#include "NinePatchImage.h"
#include "TextPassage.h"

namespace inGame
{
    class TalkingBalloon : public ActorBase
    {
        DEF_WEAK_GET(TalkingBalloon);
    public:
        static TalkingBalloon* Create(IMainScene *scene, const std::string &text, const MatPos &pos);
    private:
        TalkingBalloon(IMainScene *scene, const std::string &text, const Vec2<double> &pos);
        SpriteTexture m_SpriteRoot = SpriteTexture::Create();
        IMainScene* m_Scene;
        std::string m_Text;

        static const inline Vec2<double> bgSize = Vec2<double>{144.0, 56.0};
        unique_ptr<NinePatchImage> m_Background;
        TextPassage m_TextPassage;

        void initBackground(IMainScene *scene);
        void initTextPassage();

        CoroTask startAppear(CoroTaskYield &yield);
    };
}


#endif //FILL_TILES_TALKINGBALLOON_H
