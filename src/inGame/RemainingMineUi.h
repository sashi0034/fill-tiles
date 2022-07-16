//
// Created by sashi0034 on 2022/07/16.
//

#ifndef FILL_TILES_REMAININGMINEUI_H
#define FILL_TILES_REMAININGMINEUI_H

#include "ActorBase.h"
#include "MainScene.h"
#include "NinePatchImage.h"
#include "TextPassage.h"
#include "MineFlowerManager.h"

namespace inGame
{

    class RemainingMineUi : public ActorBase
    {
    public:
        explicit RemainingMineUi(IMainScene *scene, MineFlowerManager *mineFlowerManager);
        void Init() override;

        void Update(IAppState *appState) override;

    private:
        SpriteTexture m_SpriteRoot = SpriteTexture::Create();
        SpriteTexture m_Icon = SpriteTexture::Create();
        static const inline Vec2<double> bgSize = Vec2<double>{80, 24};
        IMainScene* m_SceneRef;
        MineFlowerManager* m_MineFlowerManagerRef;
        unique_ptr<NinePatchImage> m_Background;
        unique_ptr<TextPassage> m_TextPassage;
        int m_RemainingCountBefore = 0;

        void initText(IMainScene *scene, const std::string &str);

        void initBackground(IMainScene *scene);
    };

} // inGame

#endif //FILL_TILES_REMAININGMINEUI_H
